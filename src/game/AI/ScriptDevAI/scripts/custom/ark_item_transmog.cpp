/*
 * This file is part of the CMaNGOS Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "AI/ScriptDevAI/include/precompiled.h"
#include "ark_common.h"

#pragma execution_character_set("UTF-8") 

 /*####################
 ## ark_item_transmog
 ######################*/

void _ItemThisTransmog(Player* pPlayer, Item* pItem, Item* pTargets)
{
    uint32 itemQuality = 4;
    ArkConfig const* itr = sArkMgr.GetArkConfig("Player.transmog.quality");
    if (itr && itr->value)
        itemQuality = itr->value;

    if (pTargets->GetProto()->Quality > itemQuality)
    {
        ChatHandler(pPlayer).PSendSysMessage("[系统]: 装备不可幻化, 不支持该物品品质!");
        return;
    }
        
    // only ammor and weapon can be transmoged
    if (pTargets->GetProto()->Class != 2 && pTargets->GetProto()->Class != 4)
    {
        ChatHandler(pPlayer).PSendSysMessage("[系统]: 装备不可幻化, 不支持该物品类型!");
        return;
    }

    // skip Miscellaneous / Libram / Idol / Totem
    if (pTargets->GetProto()->Class == 4 && (pTargets->GetProto()->SubClass == 0 && (!(pTargets->GetProto()->InventoryType == 4 || pTargets->GetProto()->InventoryType == 19 || pTargets->GetProto()->InventoryType == 20))
        || pTargets->GetProto()->SubClass == 7 
        || pTargets->GetProto()->SubClass == 8
        || pTargets->GetProto()->SubClass == 9))
    {
        ChatHandler(pPlayer).PSendSysMessage("[系统]: 装备不可幻化, 该类型禁止幻化!");
        return;
    }   

    // find the slot of the item
    uint8 slots[4];
    pPlayer->ViableEquipSlots(pTargets->GetProto(), &slots[0], true);
    uint8 slot = slots[0];

    if (Item* titem = pPlayer->GetItemByPos(INVENTORY_SLOT_BAG_0, slot))
    {
        if (titem->GetEntry() == pTargets->GetEntry())
        {
            ChatHandler(pPlayer).PSendSysMessage("[系统]: 选择的幻化物品与穿戴的装备相同, 不可幻化!");
            return;
        }

        //Dual Weapon
        if (slot == EQUIPMENT_SLOT_MAINHAND && pPlayer->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND) && (pTargets->GetProto()->InventoryType == INVTYPE_WEAPON))
        {
            if (Item* OnHandWeaponItem = pPlayer->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND))
            {
                if ((OnHandWeaponItem->GetProto()->Class == pTargets->GetProto()->Class) && (OnHandWeaponItem->GetProto()->SubClass == pTargets->GetProto()->SubClass) && (OnHandWeaponItem->GetProto()->InventoryType == INVTYPE_WEAPON))
                    slot = EQUIPMENT_SLOT_OFFHAND;
                else
                {
                    if ((titem->GetProto()->Class == pTargets->GetProto()->Class) && (titem->GetProto()->SubClass == pTargets->GetProto()->SubClass))
                        slot = EQUIPMENT_SLOT_MAINHAND;
                    else
                    {
                        ChatHandler(pPlayer).PSendSysMessage("[系统]: 装备不可幻化, 不支持跨类型幻化!");
                        return;
                    }
                        
                }
            }
        }
        else
        {
            if ((slot == EQUIPMENT_SLOT_MAINHAND && pPlayer->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND)) || (slot == EQUIPMENT_SLOT_OFFHAND && pPlayer->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND)))
            {
                if (titem->GetProto()->Class != pTargets->GetProto()->Class || titem->GetProto()->SubClass != pTargets->GetProto()->SubClass)
                {
                    ChatHandler(pPlayer).PSendSysMessage("[系统]: 装备不可幻化, 不支持跨类型幻化!");
                    return;
                }    
            }
        }

        // save to db
        uint32 guid = pTargets->GetOwnerGuid().GetCounter();
        CharacterDatabase.BeginTransaction();
        // remove old transmog
        CharacterDatabase.PExecute("DELETE FROM _ark_characters_transmog WHERE guid = %u AND slot = %u", guid, slot);
        // insert new transmog
        CharacterDatabase.PExecute("INSERT INTO _ark_characters_transmog VALUES ('%u', '%u', '%u', '%u')", guid, slot, pTargets->GetGUIDLow(), 0);
        CharacterDatabase.CommitTransaction();

        // make transmogrification effect
        pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 + (slot * MAX_VISIBLE_ITEM_OFFSET), pTargets->GetEntry());

        // remove the transmog stone
        uint32 count = 1;
        pPlayer->DestroyItemCount(pItem, count, true);

        ChatHandler(pPlayer).PSendSysMessage("[系统]: |cFF33CCFF装备幻化成功!|r");
    }
    return;
}

bool OnItemWrapUseTransmog(Player* pPlayer, Item* pItem, Item* pTargets)
{
    pPlayer->CastStop();
    if (!pPlayer->isInCombat())
    {
        if (!pTargets || !pItem)
            return true;

        _ItemThisTransmog(pPlayer, pItem, pTargets);
        return true;
    }

    return true;
}

void AddSC_ark_item_transmog()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "ark_item_transmog";
    pNewScript->pItemWrapUse = &OnItemWrapUseTransmog;
    pNewScript->RegisterSelf(false);
}
