/**
* ScriptData
* SDName:      scripted_on_events
* SD%Complete: n/n
* SDComment:   Custom script hooks
* EndScriptData
**/

#include "AI/ScriptDevAI/include/precompiled.h"
#include "World/World.h"
#include "ark_common.h"
#include "Tools/Language.h"
#include <cstring>

//This function is called when the player logs in (every login)  
void OnLogin(Player* pPlayer, bool Loginfirst)
{
    sArkMgr.SetAccountExtra(pPlayer->GetSession()->GetAccountId());

    ArkConfig const* itr;
    //vip login
    pPlayer->m_vipLevel = sArkMgr.GetVipLevel(pPlayer->GetSession()->GetAccountId());
    pPlayer->m_title = "";
    pPlayer->m_nameColor = "";
    pPlayer->m_chatColor = "";
    pPlayer->m_addAutojf = 0;
    pPlayer->m_lootRate = 0.0f;
    pPlayer->m_healthRate = 0.0f;
    pPlayer->m_dmgRate = 0.0f;
    pPlayer->m_cureRate = 0.0f;
    pPlayer->m_xpRate = 0.0f;
    pPlayer->m_reputationRate = 0.0f;
    pPlayer->m_adduppro = 0.0f;
    pPlayer->m_vipAura = 0;
    pPlayer->m_talent = 0;

    std::string description;
    uint32 extra_talent = 0;
    itr = sArkMgr.GetArkConfig("Player.vipSystem");
    ArkVipSystem const* vipitr = sArkMgr.GetArkVipSystem(pPlayer->m_vipLevel);
    if (vipitr && itr && itr->value == 1)
    {
        pPlayer->m_title = vipitr->title;
        pPlayer->m_nameColor = vipitr->nameColor;
        pPlayer->m_chatColor = vipitr->chatColor;
        pPlayer->m_addAutojf = vipitr->addAutojf;
        pPlayer->m_lootRate = vipitr->lootRate;
        pPlayer->m_healthRate = vipitr->healthRate;
        pPlayer->m_dmgRate = vipitr->dmgRate;
        pPlayer->m_cureRate = vipitr->cureRate;
        pPlayer->m_xpRate = vipitr->xpRate;
        pPlayer->m_reputationRate = vipitr->reputationRate;
        pPlayer->m_adduppro = vipitr->adduppro;
        pPlayer->m_vipAura = vipitr->aura;
        pPlayer->m_talent = vipitr->talent;
        description = vipitr->description;

        //Reset Health
        if (pPlayer->m_healthRate)
        {
            pPlayer->UpdateAllStats();
            pPlayer->SetHealth(pPlayer->GetMaxHealth());
        }
    }

    //chatColor
    if (pPlayer->m_chatColor.empty())
        pPlayer->m_chatColor = "cFF00FF00";

    //Talent
    extra_talent = pPlayer->m_talent;
    extra_talent += pPlayer->m_extra_talent;

    //Init extra Talent
    if (extra_talent)
        pPlayer->InitTalentForLevel();

    //Init Aura
    sArkMgr.ResetVipAura(pPlayer);
    if (pPlayer->m_vipAura)
        pPlayer->CastSpell(pPlayer, pPlayer->m_vipAura, TRIGGERED_NONE);

    // login hint
    itr = sArkMgr.GetArkConfig("Player.login");
    if (itr && itr->value >= 1)
    {
        if (pPlayer->m_nameColor.empty())
            pPlayer->m_nameColor = "cFFFF00CC";

        std::string name = "|";
        name += pPlayer->m_nameColor;
        name += pPlayer->GetName();
        name += "|r";

        std::string title = pPlayer->m_title;

        std::string raceName = pPlayer->GetSession()->GetMangosString(LANG_COMMAND_GRAVEYARD_HORDE);   //horde
        if (pPlayer->GetTeam() == ALLIANCE)
            raceName = pPlayer->GetSession()->GetMangosString(LANG_COMMAND_GRAVEYARD_ALLIANCE);        //alliance

        switch (itr->value)
        {
        case 1:     //First
        {
            if (!Loginfirst)
                break;

            if (itr->cost == 1)
                sWorld.SendWorldText(LANG_ARK_PLAYER_LONGIN_FIRST, title.c_str(), name.c_str(), raceName.c_str());
            else
                sWorld.SendWorldText(LANG_ARK_PLAYER_LONGIN_FIRST, name.c_str(), title.c_str(), raceName.c_str());
            break;
        }
        case 2:
        {
            if (Loginfirst)
                break;

            if (itr->cost == 1)
                sWorld.SendWorldText(LANG_ARK_PLAYER_LONGIN, title.c_str(), name.c_str(), raceName.c_str());
            else
                sWorld.SendWorldText(LANG_ARK_PLAYER_LONGIN, name.c_str(), title.c_str(), raceName.c_str());

            break;
        }
        case 3:   //all
        {
            if (Loginfirst)
            {
                if (itr->cost == 1)
                    sWorld.SendWorldText(LANG_ARK_PLAYER_LONGIN_FIRST, title.c_str(), name.c_str(), raceName.c_str());
                else
                    sWorld.SendWorldText(LANG_ARK_PLAYER_LONGIN_FIRST, name.c_str(), title.c_str(), raceName.c_str());
            }
            else
            {
                if (itr->cost == 1)
                    sWorld.SendWorldText(LANG_ARK_PLAYER_LONGIN, title.c_str(), name.c_str(), raceName.c_str());
                else
                    sWorld.SendWorldText(LANG_ARK_PLAYER_LONGIN, name.c_str(), title.c_str(), raceName.c_str());
            }

            break;
        }
        default:
            break;
        }
    }

    //vip description
    if (!description.empty())
        ChatHandler(pPlayer).PSendSysMessage(description.c_str());

}

//This function is called when the player logs out   
void OnLogout(Player* /*pPlayer*/)
{

}

//This function is called when the player kills another player  
void OnPVPKill(Player* /*killer*/, Player* /*killed*/)
{

}

//This function is called when the player kills a creature
void OnCreatureKill(Player* /*killer*/, Creature* /*killed*/)
{

}

//This function is called when the player gets killed by a creature  
void OnPlayerKilledByCreature(Creature* /*killer*/, Player* /*killed*/)
{

}

//This function is called just before the players level changes   
void OnPlayerLevelChanged(Player* /*pPlayer*/, uint8 /*oldLevel*/, uint8 /*newLevel*/)
{

}

//This function is called when the player resets his talents  
void OnPlayerTalentsReset(Player* /*pPlayer*/, bool /*no_cost*/)
{

}

// Called when the world is started.
void OnStartup()
{
    sLog.outString("============================================================================================");
    sLog.outString("Loaded ARK Config...");
    sArkMgr.LoadArkConfig();
    sLog.outString("Loaded Ark Vip System...");
    sArkMgr.LoadArkVipSystem();
    sLog.outString("Loaded ARK Instance Config...");
    sArkMgr.LoadArkInstanceDB();
    sLog.outString("Loaded ARK Npc Menu Config...");
    sArkMgr.LoadArkNpcMenuDB();
    sLog.outString("============================================================================================");
    sLog.outString("Ark Loaded end, Now you ready to play.");
    sLog.outString("");
}

// Called when the world is actually shut down.
void OnShutdown()
{

}

 void AddSC_onevents()
 {
    Script* pNewScript;
    pNewScript = new Script;
    pNewScript->Name = "scripted_on_events";
    pNewScript->pOnLogin = &OnLogin;
    pNewScript->pOnLogout = &OnLogout;
    pNewScript->pOnPVPKill = &OnPVPKill;
    pNewScript->pOnCreatureKill = &OnCreatureKill;
    pNewScript->pOnPlayerKilledByCreature = &OnPlayerKilledByCreature;
    pNewScript->pOnLevelChanged = &OnPlayerLevelChanged;
    pNewScript->pOnTalentsReset = &OnPlayerTalentsReset;
    pNewScript->pOnStartup = &OnStartup;
    pNewScript->pOnShutdown = &OnShutdown;
    pNewScript->RegisterSelf(false);
} 
