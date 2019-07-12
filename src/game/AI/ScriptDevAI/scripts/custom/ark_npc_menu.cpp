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
#include "Chat/Chat.h"

#pragma execution_character_set("UTF-8") 

 /*####################
 ## ark_npc_menu
 ######################*/

void _ShowNpcTeleportMenu(uint32 MenuId, Player* pPlayer, Creature* pCreature)
{
    uint32 faction = 0;
    if (pPlayer->GetTeam() == ALLIANCE)
        faction = 1;
    else if (pPlayer->GetTeam() == HORDE)
        faction = 2;

    pPlayer->PlayerTalkClass->ClearMenus();

    //for NpcTeleportList
    auto NpcTeleports = sArkMgr.GetNpcMenus();
    for (auto itr = NpcTeleports.begin(); itr != NpcTeleports.end(); ++itr)
    {
        if (itr->second.id == MenuId && (itr->second.faction == 0 || faction == itr->second.faction || pPlayer->isGameMaster()))
        {
            if (itr->second.npcEntry == 0 || itr->second.npcEntry == pCreature->GetEntry()) 
            {
                if (itr->second.box_text.empty())
                    pPlayer->ADD_GOSSIP_ITEM(itr->second.option_icon, itr->second.option_text.c_str(), itr->second.menu_id, itr->second.option_id + 1000);
                else
                    pPlayer->ADD_GOSSIP_ITEM_EXTENDED(itr->second.option_icon, itr->second.option_text.c_str(), itr->second.menu_id, itr->second.option_id + 1000, itr->second.box_text, 0, false);
            }
                
        }
    }

    pPlayer->SEND_GOSSIP_MENU(99999, pCreature->GetObjectGuid());
    return;
}

bool _NpcTeleportCostCheck(Player* pPlayer, Creature* pCreature, uint32 uiSender)
{
    ArkMenuConfig const* itr = sArkMgr.GetArkNpcMenuConfig(uiSender);
    if (!itr)
        return false;

    switch (itr->needType)
    {
    case 1://需要人物等级
        if (pPlayer->getLevel() < (uint32)itr->needValue)
        {
            ChatHandler(pPlayer).PSendSysMessage("[系统]: 角色等级不足, 需要等级[|cff00ff00%u|r]!", itr->needValue);
            pPlayer->CLOSE_GOSSIP_MENU();
            return false;
        }
        break;
    case 2://需要VIP等级
        if (pPlayer->m_vipLevel < (uint32)itr->needValue)
        {
            ChatHandler(pPlayer).PSendSysMessage("[系统]: 帐号会员等级不足, 需要会员等级[|cff00ff00%u|r]!", itr->needValue);
            pPlayer->CLOSE_GOSSIP_MENU();
            return false;
        }
        break;
    case 3://需要积分
        if (sArkMgr.Getjf(pPlayer->GetSession()->GetAccountId()) < (uint32)itr->needValue)
        {
            ChatHandler(pPlayer).PSendSysMessage("[系统]: 帐号积分不足, 需要积分[|cff00ff00%u|r]!", (uint32)itr->needValue);
            pPlayer->CLOSE_GOSSIP_MENU();
            return false;
        }
        sArkMgr.Addjf(pPlayer->GetSession()->GetAccountId(), -(int32)itr->needValue);
        break;
    case 4://需要金币
        if (pPlayer->GetMoney() < (uint32)abs(itr->needValue * 10000))
        {
            ChatHandler(pPlayer).PSendSysMessage("[系统]: 角色金币不足, 需要金币[|cff00ff00%u|r]!", itr->needValue);
            pPlayer->CLOSE_GOSSIP_MENU();
            return false;
        }
        pPlayer->ModifyMoney(-(int32)(itr->needValue * 10000));
        break;
    case 5: // 需要物品
        if (pPlayer->GetItemCount(itr->needValue) < (uint32)abs(itr->needValue2))
        {
            std::string name = sArkMgr.GetItemNameByEntry(pPlayer, itr->needValue, true);
            ChatHandler(pPlayer).PSendSysMessage("[系统]: 背包物品不足, 需要物品, %s|cff00ff00x%u|r.", name.c_str(), (uint32)abs(itr->needValue2));
            pPlayer->CLOSE_GOSSIP_MENU();
            return false;
        }
        if (itr->needValue2 > 0) 
            pPlayer->DestroyItemCount(itr->needValue, (uint32)abs(itr->needValue2), true);
        break;
    }
    return true;
}

bool GossipHello_ark_npc_menu(Player* pPlayer, Creature* pCreature)
{
    _ShowNpcTeleportMenu(0, pPlayer, pCreature);
    return true;
}

bool GossipSelect_ark_npc_menu(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (pPlayer->isInCombat())
    {
        return false;
    }

    ArkMenuConfig const* itr = sArkMgr.GetArkNpcMenuConfig(uiSender);
    if (!itr)
        return false;

    switch (uiAction)
    {
    case 1000: // 显示指定菜单
        if (_NpcTeleportCostCheck(pPlayer, pCreature, uiSender))
        {
            _ShowNpcTeleportMenu(uiSender, pPlayer, pCreature);
        }
        return true;
    case 1001://传送
        if (_NpcTeleportCostCheck(pPlayer, pCreature, uiSender))
        {
            pPlayer->TeleportTo(itr->map, itr->x, itr->y, itr->z, itr->o);
        }
        break;
    case 1002://积分查询
        if (_NpcTeleportCostCheck(pPlayer, pCreature, uiSender))
        {
            pPlayer->GetSession()->SendNotification("|cFFFFFF33你当前帐户积分：|r|cFF33FF00%u|r ", sArkMgr.Getjf(pPlayer->GetSession()->GetAccountId()));
        }
        break;
    case 1003://领取充值积分
        {
            uint32 AccountId = pPlayer->GetSession()->GetAccountId();
            uint32 Accountjf = sArkMgr.Getjf(AccountId);
            uint32 Rechargejf = sArkMgr.GetRechargejf(AccountId);
            uint32 RechargeAll = sArkMgr.GetRechargeAll(AccountId);
            sArkMgr.SetAccountRecharge(AccountId);
            ChatHandler(pPlayer).PSendSysMessage("[系统]: 帐户剩余积分[|cFF33FF00%u|r], 领取充值积分[|cFF33FF00%u|r], 累计充值[|cFF33FF00%u|r]. ", Accountjf,  Rechargejf, RechargeAll);
        }
        break;
    case 1004: // 修理装备
        if (_NpcTeleportCostCheck(pPlayer, pCreature, uiSender))
        {
            pPlayer->GetSession()->SendNotification("|cFFFFFF33你的装备已经全部修理！|r");
            pPlayer->DurabilityRepairAll(false, 0, false);
        }
        break;
    case 1005: // 个人银行
        if (_NpcTeleportCostCheck(pPlayer, pCreature, uiSender))
        {
            pPlayer->GetSession()->SendShowBank(pPlayer->GetObjectGuid());
        }
        break;
    case 1006: //商店
        if (_NpcTeleportCostCheck(pPlayer, pCreature, uiSender))
        {
            if (itr->map > 0)
                pPlayer->GetSession()->SendListInventory(pCreature->GetObjectGuid(), itr->map);
            else
                pPlayer->SEND_VENDORLIST(pCreature->GetObjectGuid());
            return true;
        }
        break;
    case 1007: //修改名称
        if (_NpcTeleportCostCheck(pPlayer, pCreature, uiSender))
        {
            pPlayer->SetAtLoginFlag(AT_LOGIN_RENAME);    
            pPlayer->GetSession()->SendNotification("你需要重新登录，然后才能修改角色的名字！");
        }
        break;
    case 1008: //绑定炉石
        if (_NpcTeleportCostCheck(pPlayer, pCreature, uiSender))
        {
            pPlayer->GetSession()->SendBindPoint(pCreature);
        }
        break;
    case 1009: //隐藏战袍
        if (_NpcTeleportCostCheck(pPlayer, pCreature, uiSender))
        {

        }
        break;
    case 1010: //给予物品
        if (sArkMgr.CheckNullBag(pPlayer, itr->map, (uint32)itr->x))
        {
            if (_NpcTeleportCostCheck(pPlayer, pCreature, uiSender))
                sArkMgr.AddItem(pPlayer, itr->map, (uint32)itr->x);
        }
        break;
    case 1011: //给予BUFF
        if (_NpcTeleportCostCheck(pPlayer, pCreature, uiSender))
        {
            if (itr->map)
                pPlayer->CastSpell(pPlayer, itr->map, TRIGGERED_NONE);
        }
        break;
    case 1100://重置副本
        if (_NpcTeleportCostCheck(pPlayer, pCreature, uiSender))
        {
            pPlayer->UnbindInstance(itr->map, REGULAR_DIFFICULTY);
            ChatHandler(pPlayer).PSendSysMessage("[系统]: 当前副本已经重置, 地图ID[|cff00ff00%u|r]!", itr->map);
        }
        break;
    case 1999: // 指定显示某一组的菜单
        if (_NpcTeleportCostCheck(pPlayer, pCreature, uiSender))
        {
            _ShowNpcTeleportMenu(itr->map, pPlayer, pCreature);
        }
        return true;
    }
    pPlayer->CLOSE_GOSSIP_MENU();
    return true;
}

void AddSC_ark_npc_menu()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "ark_npc_menu";
    pNewScript->pGossipHello = &GossipHello_ark_npc_menu;
    pNewScript->pGossipSelect = &GossipSelect_ark_npc_menu;
    pNewScript->RegisterSelf(false);
}
