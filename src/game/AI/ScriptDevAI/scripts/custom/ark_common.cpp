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
#include <string.h>

#pragma execution_character_set("UTF-8")


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

    QueryResult* result = WorldDatabase.PQuery("SELECT entry, value, cost FROM _ark_config");

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

    QueryResult* result = WorldDatabase.PQuery("SELECT entry, title, nameColor, chatColor, reqItem, jfCost, everyDayItem, addAutojf, lootRate, healthRate, dmgRate, cureRate, xpRate, reputationRate, adduppro, aura, talent, description FROM _ark_vip_system");

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

    QueryResult* result = WorldDatabase.PQuery("SELECT map, level, Creaturelevel, Herolevel, HeroCreaturelevel FROM _ark_instance_template");

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
        itr.Herolevel = fields[3].GetUInt32();
        itr.HeroCreaturelevel = fields[4].GetUInt32();

        //insert
        _arkInstanceStore[map] = itr;

        ++count;
    } while (result->NextRow());

    delete result;

    sLog.outString(">> Loaded %u ARK Instance Config", count);
}

//Instance difficulty level
float ArkMgr::InstanceLevel(uint32 mapid, bool Heroic)
{
    ArkInstanceConfig const* itr = GetArkInstanceConfig(mapid);
    if (!itr)
        return 0.0f;

    //Hero Instance
    if (Heroic)
    {
        if (itr->Herolevel <= 0)
            return 0.0f;

        return (float)itr->Herolevel / 10;
    }
    else
    {
        if (itr->level <= 0)
            return 0.0f;

        return (float)itr->level / 10;
    }
}

void ArkMgr::InstanceCreatureLevel(uint32 mapid, bool Heroic, uint32& value)
{
    if (value <= 1)
        return;

    ArkInstanceConfig const* itr = GetArkInstanceConfig(mapid);
    if (!itr)
        return;

    //Hero Instance
    if (Heroic)
    {
        if (itr->HeroCreaturelevel <= 0)
            return;

        value += itr->HeroCreaturelevel;
    } 
    else
    {
        if (itr->Creaturelevel <= 0)
            return;

        value += itr->Creaturelevel;
    }  

    if (value > DEFAULT_MAX_CREATURE_LEVEL)
        value = uint32(DEFAULT_MAX_CREATURE_LEVEL);

    return;
}

bool ArkMgr::IsFlyInstantArrive(uint32 guid) const
{
    ArkConfig const* itr;
    itr = sArkMgr.GetArkConfig("Player.world.fly");
    if (itr)
    {
        if (itr->value == 1)
            return true;

        if (itr->value == 2)
        {
            QueryResult* result = CharacterDatabase.PQuery("SELECT guid, fly_last_date FROM _ark_characters_extra WHERE guid = '%u' AND fly_last_date >= NOW()", guid);
            if (result)
            {
                delete result;
                return true;
            }    
        }

        return false;
    }

    return false;
}

void ArkMgr::SetFlyInstantArriveDate(uint32 guid, uint32 value)
{
    if (value <= 0)
        return;

    time_t now = time(nullptr);
    time_t last_date = time_t(0);
    char sTimeDate[128] = { 0 };
    QueryResult* result = CharacterDatabase.PQuery("SELECT guid, UNIX_TIMESTAMP(fly_last_date) FROM _ark_characters_extra WHERE guid = '%u'", guid);
    if (result)
    {
        Field* fields = result->Fetch();
        last_date = time_t(fields[1].GetUInt64());
        if (last_date > now)
            last_date += value;
        else
            last_date = now + value;

        strftime(sTimeDate, 64, "%Y-%m-%d %H:%M:%S", localtime(&last_date));
        CharacterDatabase.PExecute("UPDATE _ark_characters_extra SET fly_last_date = '%s' WHERE guid = '%u'", sTimeDate, guid);
        delete result;
    }
    else
    {
        last_date = now + value;
        strftime(sTimeDate, 64, "%Y-%m-%d %H:%M:%S", localtime(&last_date));
        QueryResult* resultguld = CharacterDatabase.PQuery("SELECT guid FROM _ark_characters_extra WHERE guid = '%u'", guid);
        if (resultguld)
        {
            CharacterDatabase.PExecute("UPDATE _ark_characters_extra SET fly_last_date = '%s' WHERE guid = '%u'", sTimeDate, guid);
            delete resultguld;
        }
        else
            CharacterDatabase.PExecute("INSERT INTO _ark_characters_extra (guid, fly_last_date) VALUES ('%u', '%s')", guid, sTimeDate);

    }
}

void ArkMgr::LoadArkNpcMenuDB()
{
    // For reload case
    _arkNpcMenuStore.clear();

    QueryResult* result = WorldDatabase.PQuery("SELECT * FROM _ark_npc_menu");

    if (!result)
    {
        sLog.outErrorDb(">> Loaded 0 ARK npc menu Config. DB table `_ark_npc_menu` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        ArkMenuConfig itr;

        itr.menu_id = fields[0].GetUInt32();
        itr.id = fields[1].GetUInt32();
        itr.npcEntry = fields[2].GetUInt32();
        itr.option_icon = fields[3].GetUInt32();
        itr.option_id = fields[4].GetUInt32();
        itr.option_text = fields[5].GetString();
        itr.box_text = fields[6].GetString();
        itr.faction = fields[7].GetUInt32();
        itr.needType = fields[8].GetUInt32();
        itr.needValue = fields[9].GetInt32();
        itr.needValue2 = fields[10].GetInt32();
        itr.map = fields[11].GetUInt32();
        itr.x = fields[12].GetFloat();
        itr.y = fields[13].GetFloat();
        itr.z = fields[14].GetFloat();
        itr.o = fields[15].GetFloat();
        
        //insert
        _arkNpcMenuStore[itr.menu_id] = itr;

        ++count;
    } while (result->NextRow());

    delete result;

    sLog.outString(">> Loaded %u ARK npc Menu Config", count);
}

std::string ArkMgr::GetItemNameByEntry(Player* player, uint32 entry, bool showchat) const
{
    std::string name = "Unknown";
    ItemPrototype const* itemProto = sObjectMgr.GetItemPrototype(entry);
    if (itemProto)
    {
        name = itemProto->Name1;
        int loc_idx = player->GetSession()->GetSessionDbLocaleIndex();
        sObjectMgr.GetItemLocaleStrings(itemProto->ItemId, loc_idx, &name);

        std::string tempname;
        std::string color;

        if (itemProto->Quality > MAX_ITEM_QUALITY)
            color = "cffffffff";
        else
            color = ArkItemQualityColors[itemProto->Quality];

        if (showchat)
            tempname = "|" + color + "|Hitem:" + std::to_string(entry) + ":0:0:0:0:0:0:0|h[" + name + "]|h|r";
        else
            tempname = "|" + color + "[" + name + "]|r";

        return tempname;
    }
    return name;
}

bool ArkMgr::CheckNullBag(Player* player, uint32 itemId, uint32 count)
{
    uint32 noSpaceForCount = 0;

    // check space and find places
    ItemPosCountVec dest;
    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, itemId, count, &noSpaceForCount);
    if (msg != EQUIP_ERR_OK)                                // convert to possible store amount
        count = noSpaceForCount;

    if (count == 0 || dest.empty())
    {
        ChatHandler(player).PSendSysMessage("[系统]: 背包物品空间不足!");
        return false;
    }

    return true;
}

bool ArkMgr::AddItem(Player* player, uint32 itemId, uint32 count)
{
    uint32 noSpaceForCount = 0;

    // check space and find places
    ItemPosCountVec dest;
    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, itemId, count, &noSpaceForCount);
    if (msg != EQUIP_ERR_OK)                                // convert to possible store amount
        count -= noSpaceForCount;

    if (count == 0 || dest.empty())
    {
        ChatHandler(player).PSendSysMessage(LANG_ITEM_CANNOT_CREATE, itemId, noSpaceForCount);
        return false;
    }

    Item* item = player->StoreNewItem(dest, itemId, true, Item::GenerateItemRandomPropertyId(itemId));
    if (item)
        player->SendNewItem(item, count, true, false);
    else
        return false;

    return true;
}

void ArkMgr::LoadArkItemEnchantmentDB()
{
    // For reload case
    _arkItemEnchantmentStore.clear();

    QueryResult* result = WorldDatabase.PQuery("SELECT * FROM _ark_item_enchantment");

    if (!result)
    {
        sLog.outErrorDb(">> Loaded 0 ARK npc menu Config. DB table `_ark_item_enchantment` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        ArkItemEnchantment itr;

        itr.entry = fields[0].GetUInt32();
        itr.title1 = fields[1].GetString();
        itr.title2 = fields[2].GetString();
        itr.title3 = fields[3].GetString();
        itr.title4 = fields[4].GetString();
        itr.title5 = fields[5].GetString();
        itr.enchantmentid1 = fields[6].GetUInt32();
        itr.enchantmentid2 = fields[7].GetUInt32();
        itr.enchantmentid3 = fields[8].GetUInt32();
        itr.enchantmentid4 = fields[9].GetUInt32();
        itr.enchantmentid5 = fields[10].GetUInt32();
        itr.inventoryType = fields[11].GetUInt32();
        itr.chance = fields[12].GetUInt32();
        itr.jf = fields[13].GetUInt32();
        itr.gold = fields[14].GetUInt32();
        itr.vipLevel = fields[15].GetUInt32();
        itr.reqItem1 = fields[16].GetUInt32();
        itr.reqItem2 = fields[17].GetUInt32();
        itr.reqItem3 = fields[18].GetUInt32();
        itr.reqItem4 = fields[19].GetUInt32();
        itr.reqItem5 = fields[20].GetUInt32();
        itr.reqCount1 = fields[21].GetUInt32();
        itr.reqCount2 = fields[22].GetUInt32();
        itr.reqCount3 = fields[23].GetUInt32();
        itr.reqCount4 = fields[24].GetUInt32();
        itr.reqCount5 = fields[25].GetUInt32();
        //insert
        _arkItemEnchantmentStore[itr.entry] = itr;

        ++count;
    } while (result->NextRow());

    delete result;

    sLog.outString(">> Loaded %u ARK Item Enchantment Config", count);
}

void ArkMgr::LoadArkItemTransmog(Player* player)
{
    QueryResult* transmog = CharacterDatabase.PQuery("SELECT slot, item_guid FROM _ark_characters_transmog WHERE guid = '%u'", player->GetGUIDLow());
    if (transmog)
    {
        do
        {
            Field* fields = transmog->Fetch();
            Item* pItem = player->GetItemByGuid(ObjectGuid(HIGHGUID_ITEM, fields[1].GetUInt32()));
            if (pItem)
                player->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 + (fields[0].GetUInt8() * MAX_VISIBLE_ITEM_OFFSET), pItem->GetEntry());
            else
                CharacterDatabase.PExecute("DELETE FROM _ark_characters_transmog WHERE guid = %u AND slot = %u", player->GetGUIDLow(), fields[0].GetUInt8());

        } while (transmog->NextRow());

        delete transmog;
    }
}

void ArkMgr::LearnTrainer(Player* player, uint32 templateid)
{
    TrainerSpellData const* tSpells = sObjectMgr.GetNpcTrainerTemplateSpells(templateid);
    if (!tSpells)
        return;

    for (auto itr = tSpells->spellList.begin(); itr != tSpells->spellList.end(); ++itr)
    {
        TrainerSpell const* trainer_spell = &itr->second;

        // Not found anywhere, cheating?
        if (!trainer_spell)
            continue;

        uint32 spellId = trainer_spell->spell;

        if (!spellId)
            continue;

        uint32 reqLevel = 0;
        if (!player->IsSpellFitByClassAndRace(trainer_spell->learnedSpell, &reqLevel))
            continue;

        reqLevel = trainer_spell->isProvidedReqLevel ? trainer_spell->reqLevel : std::max(reqLevel, trainer_spell->reqLevel);
        if (player->GetTrainerSpellState(trainer_spell, reqLevel) != TRAINER_SPELL_GREEN)
            continue;

        // learn explicitly or cast explicitly
        // TODO - Are these spells really cast correctly this way?
        if (trainer_spell->IsCastable())
            player->CastSpell(player, trainer_spell->spell, TRIGGERED_OLD_TRIGGERED);
        else
            player->learnSpell(spellId, false);
    }
}

void ArkMgr::LearnLevelTrainer(Player* player)
{
    if (player->getLevel() > sWorld.getConfig(CONFIG_UINT32_MAX_PLAYER_LEVEL))
        return;

    switch (player->getClass())
    {
    case CLASS_WARRIOR:
        LearnTrainer(player, 11);
        break;
    case CLASS_PALADIN:
        LearnTrainer(player, 21);
        break;
    case CLASS_HUNTER:
        LearnTrainer(player, 31);
        break;
    case CLASS_ROGUE:
        LearnTrainer(player, 41);
        break;
    case CLASS_PRIEST:
        LearnTrainer(player, 51);
        break;
    case CLASS_SHAMAN:
        LearnTrainer(player, 61);
        break;
    case CLASS_MAGE:
        LearnTrainer(player, 71);
        break;
    case CLASS_WARLOCK:
        LearnTrainer(player, 81);
        break;
    case CLASS_DRUID:
        LearnTrainer(player, 91);
        break;
    default:
        break;
    }
}

void ArkMgr::SetAccountRecharge(uint32 accountId)
{
    uint32 jf = GetRechargejf(accountId);
    if (jf > 0)
    {
        Addjf(accountId, jf);
        LoginDatabase.PExecute("UPDATE _ark_account_recharge SET jf = 0 WHERE id = %u", accountId);
    }
}

uint32 ArkMgr::GetRechargejf(uint32 accountId) const
{
    QueryResult* result = LoginDatabase.PQuery("SELECT jf FROM _ark_account_recharge WHERE id = %u", accountId);

    if (result)
    {
        int32 jf = (*result)[0].GetInt32();
        delete result;

        return jf;
    }
    else
    {
        return 0;
    }
}

uint32 ArkMgr::GetRechargeAll(uint32 accountId) const
{
    QueryResult* result = LoginDatabase.PQuery("SELECT amount FROM _ark_account_recharge WHERE id = %u", accountId);

    if (result)
    {
        int32 amount = (*result)[0].GetInt32();
        delete result;

        return amount;
    }
    else
    {
        return 0;
    }
}

void ArkMgr::LoadArkStatsLimitDB()
{
    // For reload case
    _arkStatsLimitStore.clear();

    QueryResult* result = WorldDatabase.PQuery("SELECT class, Agility_crit, Agility_dodge, Intellect_crit FROM _ark_stats_limit");

    if (!result)
    {
        sLog.outErrorDb(">> Loaded 0 ARK Stats Limit Config. DB table `_ark_stats_limit` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        ArkStatsLimitConfig itr;
        uint32 pClass = fields[0].GetUInt32();
        itr.Agility_crit = fields[1].GetFloat();
        itr.Agility_dodge = fields[2].GetFloat();
        itr.Intellect_crit = fields[3].GetFloat();

        //insert
        _arkStatsLimitStore[pClass] = itr;

        ++count;
    } while (result->NextRow());

    delete result;

    sLog.outString(">> Loaded %u ARK Stats Limit Config", count);
}

float ArkMgr::GetStatsLimit(uint32 Class, uint32 StatsType) const
{
    float val = 0.0f;
    ArkStatsLimitConfig const* itr = GetArkStatsLimitConfig(Class);
    if (itr)
    {
        switch (StatsType)
        {
        case 1:   // Agility crit
            {
                if (itr->Agility_crit)
                    val = itr->Agility_crit;
            }
            break;
        case 2:   // Agility dodge
            {
                if (itr->Agility_dodge)
                    val = itr->Agility_dodge;
            }
            break;
        case 3:   // Intellect crit
            {
                if (itr->Intellect_crit)
                    val = itr->Intellect_crit;
            }
            break;
        }
    }
    return val;
}

bool ArkMgr::IsDualSpecArrive(uint32 guid) const
{
    QueryResult* result = CharacterDatabase.PQuery("SELECT guid, talent_last_date FROM _ark_characters_extra WHERE guid = '%u' AND talent_last_date >= NOW()", guid);
    if (result)
    {
        delete result;
        return true;
    }
    return false;
}

void ArkMgr::SetDualSpecArriveDate(uint32 guid, uint32 value)
{
    if (value <= 0)
        return;

    time_t now = time(nullptr);
    time_t last_date = time_t(0);
    char sTimeDate[128] = { 0 };
    QueryResult* result = CharacterDatabase.PQuery("SELECT guid, UNIX_TIMESTAMP(talent_last_date) FROM _ark_characters_extra WHERE guid = '%u'", guid);
    if (result)
    {
        Field* fields = result->Fetch();
        last_date = time_t(fields[1].GetUInt64());
        if (last_date > now)
            last_date += value;
        else
            last_date = now + value;

        strftime(sTimeDate, 64, "%Y-%m-%d %H:%M:%S", localtime(&last_date));
        CharacterDatabase.PExecute("UPDATE _ark_characters_extra SET talent_last_date = '%s' WHERE guid = '%u'", sTimeDate, guid);
        delete result;
    }
    else
    {
        last_date = now + value;
        strftime(sTimeDate, 64, "%Y-%m-%d %H:%M:%S", localtime(&last_date));
        QueryResult* resultguld = CharacterDatabase.PQuery("SELECT guid FROM _ark_characters_extra WHERE guid = '%u'", guid);
        if (resultguld)
        {
            CharacterDatabase.PExecute("UPDATE _ark_characters_extra SET talent_last_date = '%s' WHERE guid = '%u'", sTimeDate, guid);
            delete resultguld;
        }
        else
            CharacterDatabase.PExecute("INSERT INTO _ark_characters_extra (guid, talent_last_date) VALUES ('%u', '%s')", guid, sTimeDate);
    }
}
