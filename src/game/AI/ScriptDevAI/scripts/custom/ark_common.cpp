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

#include "ark_common.h"


ArkMgr::ArkMgr()
{
}

ArkMgr* ArkMgr::instance()
{
    static ArkMgr instance;
    return &instance;
}

ArkMgr::~ArkMgr()
{
}

void ArkMgr::LoadArkConfig()
{
    // For reload case
    _arkConfigStore.clear();

    QueryResult* result = WorldDatabase.Query("SELECT entry, value, cost FROM _ark_config");

    if (!result)
    {
        sLog.outErrorDb(">> Loaded 0 ARK Config. DB table `_ark_config` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        std::string entry = fields[0].GetString();
        ArkConfig itr;
        itr.value = fields[1].GetUInt32();
        itr.cost = fields[2].GetUInt32();

        //insert
        _arkConfigStore[entry] = itr;

        ++count;
    } while (result->NextRow());

    delete result;

    sLog.outString(">> Loaded %u ARK Config", count);
}

void ArkMgr::SetAccountExtra(uint32 accountId)
{
    QueryResult* result = LoginDatabase.PQuery("SELECT id FROM _ark_account_Extra WHERE id = %u", accountId);

    if (result)
        delete result;
    else
        LoginDatabase.PExecute("INSERT INTO _ark_account_Extra(id, jf) VALUES(%u, 0)", accountId);
}

uint32 ArkMgr::Getjf(uint32 accountId) const
{
    QueryResult* result = LoginDatabase.PQuery("SELECT jf FROM _ark_account_Extra WHERE id = %u", accountId);

    if (result)
    {
        int32 Accountjf = (*result)[0].GetInt32();
        delete result;

        return Accountjf;
    }
    else
    {
        return 0;
    }
}

void ArkMgr::Addjf(uint32 accountId, int32 value)
{
    int32 Accountjf = Getjf(accountId);
    int32 amount = Accountjf + value;

    if (amount > 0)
        LoginDatabase.PExecute("UPDATE _ark_account_Extra SET jf = %u WHERE id = %u", amount, accountId);
    else
        LoginDatabase.PExecute("UPDATE _ark_account_Extra SET jf = %u WHERE id = %u", 0, accountId);
}

void ArkMgr::LoadArkVipSystem()
{
    // For reload case
    _arkVipSystemStore.clear();

    QueryResult* result = WorldDatabase.Query("SELECT entry, title, nameColor, chatColor, reqItem, jfCost, everyDayItem, addAutojf, lootRate, healthRate, dmgRate, cureRate, xpRate, reputationRate, adduppro, aura, talent, description FROM _ark_vip_system");

    if (!result)
    {
        sLog.outString("server.loading", ">> Loaded 0 Ark Vip System. DB table `_ark_vip_system` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 entry = fields[0].GetUInt32();
        ArkVipSystem itr;
        itr.title = fields[1].GetString();
        itr.nameColor = fields[2].GetString();
        itr.chatColor = fields[3].GetString();
        itr.reqItem = fields[4].GetUInt32();
        itr.jfCost = fields[5].GetUInt32();
        itr.everyDayItem = fields[6].GetUInt32();
        itr.addAutojf = fields[7].GetUInt32();
        itr.lootRate = fields[8].GetFloat();
        itr.healthRate = fields[9].GetFloat();
        itr.dmgRate = fields[10].GetFloat();
        itr.cureRate = fields[11].GetFloat();
        itr.xpRate = fields[12].GetFloat();
        itr.reputationRate = fields[13].GetFloat();
        itr.adduppro = fields[14].GetFloat();
        itr.aura = fields[15].GetUInt32();
        itr.talent = fields[16].GetUInt32();
        itr.description = fields[17].GetString();

        //insert
        _arkVipSystemStore[entry] = itr;

        ++count;
    } while (result->NextRow());

    delete result;

    sLog.outString(">> Loaded %u Ark Vip System", count);
}

uint32 ArkMgr::GetVipLevel(uint32 accountId) const
{
    QueryResult* result = LoginDatabase.PQuery("SELECT viplevel FROM _ark_account_Extra WHERE id = %u", accountId);

    if (result)
    {
        int32 VipLevel = (*result)[0].GetInt32();
        delete result;

        return VipLevel;
    }
    else
    {
        return 0;
    }
}

void ArkMgr::SetVipLevel(uint32 accountId, uint32 value)
{
    LoginDatabase.PExecute("UPDATE _ark_account_Extra SET viplevel = %u WHERE id = %u", value, accountId);
}

void ArkMgr::ResetVipAura(Player* player)
{
    if (_arkVipSystemStore.empty())
        return;

    //For
    ArkVipSystemContainer::const_iterator itr = _arkVipSystemStore.begin();
    while (itr != _arkVipSystemStore.end())
    {
        if (&itr->second && itr->second.aura && player->HasAura(itr->second.aura))
            player->RemoveAurasDueToSpell(itr->second.aura);
        ++itr;
    }
}

std::string ArkMgr::GetNameLink(Player* player, bool type)
{
    char* sIcon = "";

    if (type)
    {
        switch (player->getRace())
        {
        case RACE_HUMAN:
        {
            if (player->getGender() == 0)
                sIcon = "|TInterface\\ICONS\\Achievement_Character_Human_Male:20:20:1:-3|t";
            else
                sIcon = "|TInterface\\ICONS\\Achievement_Character_Human_Female:20:20:1:-3|t";
            break;
        }
        case RACE_ORC:
        {
            if (player->getGender() == 0)
                sIcon = "|TInterface\\ICONS\\Achievement_Character_Orc_Male:20:20:1:-3|t";
            else
                sIcon = "|TInterface\\ICONS\\Achievement_Character_Orc_Female:20:20:1:-3|t";
            break;
        }
        case RACE_DWARF:
        {
            if (player->getGender() == 0)
                sIcon = "|TInterface\\ICONS\\Achievement_Character_Dwarf_Male:20:20:1:-3|t";
            else
                sIcon = "|TInterface\\ICONS\\Achievement_Character_Dwarf_Female:20:20:1:-3|t";
            break;
        }
        case RACE_NIGHTELF:
        {
            if (player->getGender() == 0)
                sIcon = "|TInterface\\ICONS\\Achievement_Character_Nightelf_Male:20:20:1:-3|t";
            else
                sIcon = "|TInterface\\ICONS\\Achievement_Character_Nightelf_Female:20:20:1:-3|t";
            break;
        }
        case RACE_UNDEAD:
        {
            if (player->getGender() == 0)
                sIcon = "|TInterface\\ICONS\\Achievement_Character_Undead_Male:20:20:1:-3|t";
            else
                sIcon = "|TInterface\\ICONS\\Achievement_Character_Undead_Female:20:20:1:-3|t";
            break;
        }
        case RACE_GNOME:
        {
            if (player->getGender() == 0)
                sIcon = "|TInterface\\ICONS\\Achievement_Character_Gnome_Male:20:20:1:-3|t";
            else
                sIcon = "|TInterface\\ICONS\\Achievement_Character_Gnome_Female:20:20:1:-3|t";
            break;
        }
        case RACE_TROLL:
        {
            if (player->getGender() == 0)
                sIcon = "|TInterface\\ICONS\\Achievement_Character_Troll_Male:20:20:1:-3|t";
            else
                sIcon = "|TInterface\\ICONS\\Achievement_Character_Troll_Female:20:20:1:-3|t";
            break;
        }
        case RACE_BLOODELF:
        {
            if (player->getGender() == 0)
                sIcon = "|TInterface\\ICONS\\Achievement_Character_Bloodelf_Male:20:20:1:-3|t";
            else
                sIcon = "|TInterface\\ICONS\\Achievement_Character_Bloodelf_Female:20:20:1:-3|t";
            break;
        }
        case RACE_DRAENEI:
        {
            if (player->getGender() == 0)
                sIcon = "|TInterface\\ICONS\\Achievement_Character_Draenei_Male:20:20:1:-3|t";
            else
                sIcon = "|TInterface\\ICONS\\Achievement_Character_Draenei_Female:20:20:1:-3|t";
            break;
        }

        default:
            break;
        }

    }
    else
    {
        switch (player->getClass())
        {
        case CLASS_WARRIOR:
            sIcon = "|TInterface\\ICONS\\INV_Sword_27:20:20:1:-3|t";
            break;
        case CLASS_PALADIN:
            sIcon = "|TInterface\\ICONS\\INV_Hammer_01:20:20:1:-3|t";
            break;
        case CLASS_HUNTER:
            sIcon = "|TInterface\\ICONS\\INV_Weapon_Bow_07:20:20:1:-3|t";
            break;
        case CLASS_ROGUE:
            sIcon = "|TInterface\\ICONS\\INV_ThrowingKnife_04:20:20:1:-3|t";
            break;
        case CLASS_PRIEST:
            sIcon = "|TInterface\\ICONS\\INV_Staff_30:20:20:1:-3|t";
            break;
        //case CLASS_DEATH_KNIGHT:
        //    sIcon = "|TInterface\\ICONS\\Spell_Deathknight_ClassIcon:20:20:1:-3|t";
        //    break;
        case CLASS_SHAMAN:
            sIcon = "|TInterface\\ICONS\\Spell_Nature_BloodLust:20:20:1:-3|t";
            break;
        case CLASS_MAGE:
            sIcon = "|TInterface\\ICONS\\INV_Staff_13:20:20:1:-3|t";
            break;
        case CLASS_WARLOCK:
            sIcon = "|TInterface\\ICONS\\Spell_Nature_FaerieFire:20:20:1:-3|t";
            break;
        case CLASS_DRUID:
            sIcon = "|TInterface\\ICONS\\Ability_Druid_Maul:20:20:1:-3|t";
            break;
        default:
            break;
        }
    }
    return sIcon;
}

void ArkMgr::LoadArkInstanceDB()
{
    // For reload case
    _arkInstanceStore.clear();

    QueryResult* result = WorldDatabase.Query("SELECT map, level, Creaturelevel FROM _ark_instance_template");

    if (!result)
    {
        sLog.outErrorDb(">> Loaded 0 ARK Instance Config. DB table `_ark_instance_template` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        ArkInstanceConfig itr;
        uint32 map = fields[0].GetUInt32();
        itr.level = fields[1].GetUInt32();
        itr.Creaturelevel = fields[2].GetUInt32();

        //insert
        _arkInstanceStore[map] = itr;

        ++count;
    } while (result->NextRow());

    delete result;

    sLog.outString(">> Loaded %u ARK Instance Config", count);
}

//Instance difficulty level
float ArkMgr::InstanceLevel(uint32 mapid)
{
    ArkInstanceConfig const* itr = GetArkInstanceConfig(mapid);
    if (!itr || itr->level <= 0)
        return 0;

    return (float)itr->level / 10;
}

void ArkMgr::InstanceCreatureLevel(uint32 mapid, uint32& value)
{
    if (value <= 1)
        return;

    ArkInstanceConfig const* itr = GetArkInstanceConfig(mapid);
    if (!itr || itr->Creaturelevel <= 0)
        return;

    value += itr->Creaturelevel;
    if (value > DEFAULT_MAX_CREATURE_LEVEL)
        value = uint32(DEFAULT_MAX_CREATURE_LEVEL);

    return;
}
