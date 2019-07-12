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
#include "Entities/ItemEnchantmentMgr.h"
#include "ark_common.h"
#include "Chat/Chat.h"
#include "Spells/Spell.h"

#pragma execution_character_set("UTF-8") 

 /*####################
 ## ark_item_enchantment
 ######################*/

void _ShowItemEnchantmentMenu(Item* pItem, Item* target, Player* pPlayer)
{
	if (!pItem || !target || !pPlayer)
		return;

    pPlayer->PlayerTalkClass->ClearMenus();

    ArkItemEnchantment const* itr = sArkMgr.GetArkItemEnchantmentConfig(target->GetEntry());
    if (!itr)
    {
        ChatHandler(pPlayer).PSendSysMessage("[系统]: 该装备不可附魔, 请重新选择物品!");
        return;
    }

	uint32 itemClass = target->GetProto()->Class;
	if (itemClass != 2/*武器*/ && itemClass != 4/*装备护甲首饰*/)
	{
        ChatHandler(pPlayer).PSendSysMessage("[系统]: 该装备不可附魔, 请重新选择物品!");
		return;
	}

    if (itr->enchantmentid1 && !itr->title1.empty())
        pPlayer->ADD_GOSSIP_ITEM(ICON_POI_REDHORSE + 1, itr->title1.c_str(), target->GetGUIDLow(), 1000);

    if (itr->enchantmentid2 && !itr->title2.empty())
        pPlayer->ADD_GOSSIP_ITEM(ICON_POI_REDHORSE + 1, itr->title2.c_str(), target->GetGUIDLow(), 1001);

    if (itr->enchantmentid3 && !itr->title3.empty())
        pPlayer->ADD_GOSSIP_ITEM(ICON_POI_REDHORSE + 1, itr->title3.c_str(), target->GetGUIDLow(), 1002);

    if (itr->enchantmentid4 && !itr->title4.empty())
        pPlayer->ADD_GOSSIP_ITEM(ICON_POI_REDHORSE + 1, itr->title4.c_str(), target->GetGUIDLow(), 1003);

    if (itr->enchantmentid5 && !itr->title5.empty())
        pPlayer->ADD_GOSSIP_ITEM(ICON_POI_REDHORSE + 1, itr->title5.c_str(), target->GetGUIDLow(), 1004);

    pPlayer->ADD_GOSSIP_ITEM(ICON_POI_REDHORSE + 1, "|cFF0041FF退出窗口...|r", 0, 9999);
    pPlayer->SEND_GOSSIP_MENU(99999, pItem->GetObjectGuid());
}

void _ShowItemEnchantmentUp(uint32 itemGuid, Player* pPlayer, Item* pItem, uint32 EnchantmentSelectType)
{
    if (!pPlayer || !pItem)
        return;

    pPlayer->PlayerTalkClass->ClearMenus();

    Item * target = pPlayer->GetItemByGuid(ObjectGuid(HIGHGUID_ITEM, itemGuid));
    if (!target)
        return;

    uint32 TargetId = target->GetEntry();
    if (pPlayer->GetItemCount(TargetId) == 0)//IN BANK
        return;

    ArkItemEnchantment const* itr = sArkMgr.GetArkItemEnchantmentConfig(TargetId);
    if (!itr)
        return;

    std::stringstream ss;
    ss << "|cFF9933FF〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓" << "|r|n";
    ss << "|cFF9933FF〓※※重铸随机附魔材料列表※※〓" << "|r|n";
    ss << "|cFF9933FF〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓" << "|r|n";
    ss << " |n" ; 

    if (itr->reqItem1 > 0)
        ss << "|cffa335ee需要物品" << ": |r" << sArkMgr.GetItemNameByEntry(pPlayer, itr->reqItem1) << "|cFF0041FFx" << itr->reqCount1 << "|r|n";

    if (itr->reqItem2 > 0)
        ss << "|cffa335ee需要物品" << ": |r" << sArkMgr.GetItemNameByEntry(pPlayer, itr->reqItem2) << "|cFF0041FFx" << itr->reqCount2 << "|r|n";

    if (itr->reqItem3 > 0)
        ss << "|cffa335ee需要物品" << ": |r" << sArkMgr.GetItemNameByEntry(pPlayer, itr->reqItem3) << "|cFF0041FFx" << itr->reqCount3 << "|r|n";

    if (itr->reqItem4 > 0)
        ss << "|cffa335ee需要物品" << ": |r" << sArkMgr.GetItemNameByEntry(pPlayer, itr->reqItem4) << "|cFF0041FFx" << itr->reqCount1 << "|r|n";

    if (itr->reqItem5 > 0)
        ss << "|cffa335ee需要物品" << ": |r" << sArkMgr.GetItemNameByEntry(pPlayer, itr->reqItem5) << "|cFF0041FFx" << itr->reqCount1 << "|r|n";

    if (itr->jf > 0)
        ss << "|cffa335ee需要积分" << ": |r" << "|cFF0041FF" << itr->jf << "|r|n";

    if (itr->gold > 0)
        ss << "|cffa335ee需要金币" << ": |r" << "|cFF0041FF" << itr->gold << "|r|n";

    if (itr->vipLevel > 0)
        ss << "|cffa335ee会员等级" << ": |r" << "|cFF0041FF" << itr->vipLevel << "|r|n";

    uint32 chance = itr->chance;
    chance = chance > 100 ? 100 : chance;
    ss << "|cffa335ee成功几率" << ": |r|cFF0041FF" << chance << "%|r|n";

    pPlayer->ADD_GOSSIP_ITEM_EXTENDED(ICON_POI_REDHORSE + 1, ss.str().c_str(), target->GetGUIDLow(), EnchantmentSelectType + 2000, "你是否确定重铸附魔属性?", 0, false);
    pPlayer->ADD_GOSSIP_ITEM(ICON_POI_REDHORSE + 1, "|cFF0041FF退出窗口...|r", 0, 9999);
    pPlayer->SEND_GOSSIP_MENU(99999, pItem->GetObjectGuid());
}

void _ItemThisEnchantment(uint32 itemGuid, Player* pPlayer, Item* pItem, uint32 EnchantmentSelectType)
{
    //检查被升级物品数量
    if (!pPlayer || !pItem || !EnchantmentSelectType)
        return;

    Item * target = pPlayer->GetItemByGuid(ObjectGuid(HIGHGUID_ITEM, itemGuid));
    if (!target)
        return;

    uint32 TargetId = target->GetEntry();
    if (pPlayer->GetItemCount(TargetId) == 0)//IN BANK
        return;

    ArkItemEnchantment const* itr = sArkMgr.GetArkItemEnchantmentConfig(TargetId);
    if (!itr)
        return;

    if (itr->jf > 0)
    {
        if (sArkMgr.Getjf(pPlayer->GetSession()->GetAccountId()) < itr->jf)
        {
            ChatHandler(pPlayer).PSendSysMessage("[系统]: 帐号积分不足, 需要积分[|cff00ff00%u|r]!", itr->jf);
            pPlayer->CLOSE_GOSSIP_MENU();
            return;
        }
    }

    if (itr->gold > 0)
    {
        if (pPlayer->GetMoney() < itr->gold * 10000)
        {
            ChatHandler(pPlayer).PSendSysMessage("[系统]: 角色金币不足, 需要金币[|cff00ff00%u|r]!", itr->gold);
            pPlayer->CLOSE_GOSSIP_MENU();
            return;
        }
    }

    if (itr->vipLevel > 0)
    {
        if (pPlayer->m_vipLevel < itr->vipLevel)
        {
            ChatHandler(pPlayer).PSendSysMessage("[系统]: 帐号会员等级不足, 需要会员等级[|cff00ff00%u|r]!", itr->vipLevel);
            pPlayer->CLOSE_GOSSIP_MENU();
            return;
        }
    }

    if (itr->reqItem1 > 0 && itr->reqCount1 > 0)	// 需要物品1
    {
        if (pPlayer->GetItemCount(itr->reqItem1) < itr->reqCount1)
        {
            std::string name = sArkMgr.GetItemNameByEntry(pPlayer, itr->reqItem1, true);
            ChatHandler(pPlayer).PSendSysMessage("[系统]: 背包物品不足, 需要物品, %s|cff00ff00x%u|r.", name.c_str(), itr->reqCount1);
            pPlayer->CLOSE_GOSSIP_MENU();
            return;
        }
    }

    if (itr->reqItem2 > 0 && itr->reqCount2 > 0)	// 需要物品2
    {
        if (pPlayer->GetItemCount(itr->reqItem2) < itr->reqCount2)
        {
            std::string name = sArkMgr.GetItemNameByEntry(pPlayer, itr->reqItem2, true);
            ChatHandler(pPlayer).PSendSysMessage("[系统]: 背包物品不足, 需要物品, %s|cff00ff00x%u|r.", name.c_str(), itr->reqCount2);
            pPlayer->CLOSE_GOSSIP_MENU();
            return;
        }
    }

    if (itr->reqItem3 > 0 && itr->reqCount3 > 0)	// 需要物品3
    {
        if (pPlayer->GetItemCount(itr->reqItem3) < itr->reqCount3)
        {
            std::string name = sArkMgr.GetItemNameByEntry(pPlayer, itr->reqItem3, true);
            ChatHandler(pPlayer).PSendSysMessage("[系统]: 背包物品不足, 需要物品, %s|cff00ff00x%u|r.", name.c_str(), itr->reqCount3);
            pPlayer->CLOSE_GOSSIP_MENU();
            return;
        }
    }

    if (itr->reqItem4 > 0 && itr->reqCount4 > 0)	// 需要物品4
    {
        if (pPlayer->GetItemCount(itr->reqItem4) < itr->reqCount4)
        {
            std::string name = sArkMgr.GetItemNameByEntry(pPlayer, itr->reqItem4, true);
            ChatHandler(pPlayer).PSendSysMessage("[系统]: 背包物品不足, 需要物品, %s|cff00ff00x%u|r.", name.c_str(), itr->reqCount4);
            pPlayer->CLOSE_GOSSIP_MENU();
            return;
        }
    }

    if (itr->reqItem5 > 0 && itr->reqCount5 > 0)	// 需要物品5
    {
        if (pPlayer->GetItemCount(itr->reqItem5) < itr->reqCount5)
        {
            std::string name = sArkMgr.GetItemNameByEntry(pPlayer, itr->reqItem5, true);
            ChatHandler(pPlayer).PSendSysMessage("[系统]: 背包物品不足, 需要物品, %s|cff00ff00x%u|r.", name.c_str(), itr->reqCount5);
            pPlayer->CLOSE_GOSSIP_MENU();
            return;
        }
    }

    //扣除费用
    if (itr->jf > 0)
        sArkMgr.Addjf(pPlayer->GetSession()->GetAccountId(), -(int32)itr->jf);

    if (itr->gold > 0)
        pPlayer->ModifyMoney(-(int32)(itr->gold * 10000));

    if (itr->reqItem1 > 0 && itr->reqCount1 > 0)	// 需要物品1
        pPlayer->DestroyItemCount(itr->reqItem1, itr->reqCount1, true);

    if (itr->reqItem2 > 0 && itr->reqCount2 > 0)	// 需要物品2
        pPlayer->DestroyItemCount(itr->reqItem2, itr->reqCount2, true);

    if (itr->reqItem3 > 0 && itr->reqCount3 > 0)	// 需要物品3
        pPlayer->DestroyItemCount(itr->reqItem3, itr->reqCount3, true);

    if (itr->reqItem4 > 0 && itr->reqCount4 > 0)	// 需要物品4
        pPlayer->DestroyItemCount(itr->reqItem4, itr->reqCount4, true);

    if (itr->reqItem5 > 0 && itr->reqCount5 > 0)	// 需要物品5
        pPlayer->DestroyItemCount(itr->reqItem5, itr->reqCount5, true);

    uint32 chance = itr->chance;
    uint32 urand_chance = urand(1, 100);
    if (urand_chance <= chance)
    {
        //随机重铸前缀
        if (EnchantmentSelectType == 1)
            target->SetItemRandomProperties(GetItemEnchantMod(itr->enchantmentid1));
        else if (EnchantmentSelectType == 2)
            target->SetItemRandomProperties(GetItemEnchantMod(itr->enchantmentid2));
        else if (EnchantmentSelectType == 3)
            target->SetItemRandomProperties(GetItemEnchantMod(itr->enchantmentid3));
        else if (EnchantmentSelectType == 4)
            target->SetItemRandomProperties(GetItemEnchantMod(itr->enchantmentid4));
        else if (EnchantmentSelectType == 5)
            target->SetItemRandomProperties(GetItemEnchantMod(itr->enchantmentid5));

        ChatHandler(pPlayer).PSendSysMessage("[系统]: |cFF33CCFF重铸装备附魔成功, 请在背包中查看!|r");
    }
    else 
        ChatHandler(pPlayer).PSendSysMessage("[系统]: |cFF33CCFF重铸装备附魔失败, 材料消失!|r");

    pPlayer->CLOSE_GOSSIP_MENU();
    return;
}

bool OnItemWrapUse(Player* pPlayer, Item* pItem, Item* pTargets)
{
    pPlayer->CastStop();
    if (!pPlayer->isInCombat())
    {
        if (!pTargets || !pItem)
            return true;

        _ShowItemEnchantmentMenu(pItem, pTargets, pPlayer);
        return true;
    }

    return true;
}

bool GossipSelect_item_enchantment(Player* pPlayer, Item* pItem, uint32 uiSender, uint32 uiAction)
{
    switch (uiAction)
    {
    case 1000: //分配不同的附魔菜单
        _ShowItemEnchantmentUp(uiSender, pPlayer, pItem, 1);
        return true;
    case 1001:
        _ShowItemEnchantmentUp(uiSender, pPlayer, pItem, 2);
        return true;
    case 1002:
        _ShowItemEnchantmentUp(uiSender, pPlayer, pItem, 3);
        return true;
    case 1003: 
        _ShowItemEnchantmentUp(uiSender, pPlayer, pItem, 4);
        return true;
    case 1004: 
        _ShowItemEnchantmentUp(uiSender, pPlayer, pItem, 5);
        return true;
    case 2001: //升级模版
        _ItemThisEnchantment(uiSender, pPlayer, pItem, 1);
        break;
    case 2002: 
        _ItemThisEnchantment(uiSender, pPlayer, pItem, 2);
        break;
    case 2003: 
        _ItemThisEnchantment(uiSender, pPlayer, pItem, 3);
        break;
    case 2004: 
        _ItemThisEnchantment(uiSender, pPlayer, pItem, 4);
        break;
    case 2005: 
        _ItemThisEnchantment(uiSender, pPlayer, pItem, 5);
        break;
    default:
        break;
    }
    pPlayer->CLOSE_GOSSIP_MENU();
    return true;
}

void AddSC_ark_item_enchantment()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "ark_item_enchantment";
    pNewScript->pItemWrapUse = &OnItemWrapUse;
    pNewScript->pGossipSelectItem = &GossipSelect_item_enchantment;
    pNewScript->RegisterSelf(false);
}
