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

#ifndef SC_ACE_COMMON_H
#define SC_ACE_COMMON_H

#include "Common.h"
#include "Database/DatabaseEnv.h"
#include "AI/ScriptDevAI/include/precompiled.h"
#include "Time.h"
#include "Errors.h"
#include "Log.h"
#include "Tools/Language.h"
#include "World/World.h"
#include <map>
#include <unordered_map>

struct ArkConfig
{
    uint32 value;
    uint32 cost;
};

struct ArkVipSystem
{
    std::string title;
    std::string nameColor;
    std::string chatColor;
    uint32 reqItem;
    uint32 jfCost;
    uint32 everyDayItem;
    uint32 addAutojf;
    float lootRate;
    float healthRate;
    float dmgRate;
    float cureRate;
    float xpRate;
    float reputationRate;
    float adduppro;
    uint32 aura;
    uint32 talent;
    std::string description;
};

struct ArkInstanceConfig
{
    uint32 level;
    uint32 Creaturelevel;
    uint32 Herolevel;
    uint32 HeroCreaturelevel;
};

struct ArkMenuConfig
{
    uint32 menu_id;
    uint32 id;
    uint32 npcEntry;
    uint32 option_icon;
    uint32 option_id;
    std::string option_text;
    std::string box_text;
    int32 faction;
    uint32 needType;
    int32 needValue;
    int32 needValue2;
    uint32 map;
    float x;
    float y;
    float z;
    float o;
};

const std::string ArkItemQualityColors[MAX_ITEM_QUALITY] =
{
    "cff9d9d9d",        // GREY
    "cffffffff",        // WHITE
    "cff1eff00",        // GREEN
    "cff0070dd",        // BLUE
    "cffa335ee",        // PURPLE
    "cffff8000",        // ORANGE
    "cffe6cc80"         // LIGHT YELLOW
};

struct ArkItemEnchantment
{
    uint32 entry;
    std::string title1;
    std::string title2;
    std::string title3;
    std::string title4;
    std::string title5;
    uint32 enchantmentid1;
    uint32 enchantmentid2;
    uint32 enchantmentid3;
    uint32 enchantmentid4;
    uint32 enchantmentid5;
    uint32 inventoryType;
    uint32 chance;
    uint32 jf;
    uint32 gold;
    uint32 vipLevel;
    uint32 reqItem1;
    uint32 reqItem2;
    uint32 reqItem3;
    uint32 reqItem4;
    uint32 reqItem5;
    uint32 reqCount1;
    uint32 reqCount2;
    uint32 reqCount3;
    uint32 reqCount4;
    uint32 reqCount5; 
};

class ArkMgr
{
public:
    ArkMgr();
    ~ArkMgr();

    static ArkMgr* instance();

    void LoadArkConfig();
    typedef std::unordered_map<std::string, ArkConfig> ArkConfigContainer;
    ArkConfig const* GetArkConfig(std::string entry) const
    {
        ArkConfigContainer::const_iterator itr = _arkConfigStore.find(entry);
        return itr != _arkConfigStore.end() ? &itr->second : nullptr;
    }

    //AccountExtra instance
    void SetAccountExtra(uint32 accountId);
    uint32 Getjf(uint32 accountId) const;
    void Addjf(uint32 accountId, int32 value);

    void LoadArkVipSystem();
    typedef std::unordered_map<uint32, ArkVipSystem> ArkVipSystemContainer;
    ArkVipSystem const* GetArkVipSystem(uint32 entry) const
    {
        ArkVipSystemContainer::const_iterator itr = _arkVipSystemStore.find(entry);
        return itr != _arkVipSystemStore.end() ? &itr->second : nullptr;
    }

    void ResetVipAura(Player* player);
    uint32 GetVipLevel(uint32 accountId) const;
    void SetVipLevel(uint32 accountId, uint32 value);

    std::string GetNameLink(Player* player, bool type);

    //Instance difficulty level 
    void LoadArkInstanceDB();
    typedef std::unordered_map<uint32, ArkInstanceConfig> ArkInstanceContainer;
    ArkInstanceConfig const* GetArkInstanceConfig(uint32 mapid) const
    {
        ArkInstanceContainer::const_iterator itr = _arkInstanceStore.find(mapid);
        return itr != _arkInstanceStore.end() ? &itr->second : nullptr;
    }
    float InstanceLevel(uint32 mapid, bool Heroic);
    void InstanceCreatureLevel(uint32 mapid, bool Heroic, uint32& value);

    //Instant Arrive Fly
    bool IsFlyInstantArrive(uint32 guid) const;
    void SetFlyInstantArriveDate(uint32 guid, uint32 value);

    //npc Menu
    void LoadArkNpcMenuDB();
    typedef std::map<uint32, ArkMenuConfig> ArkNpcMenuContainer;
    ArkMenuConfig const* GetArkNpcMenuConfig(uint32 menu_id) const
    {
        ArkNpcMenuContainer::const_iterator itr = _arkNpcMenuStore.find(menu_id);
        return itr != _arkNpcMenuStore.end() ? &itr->second : nullptr;
    }

    std::map<uint32, ArkMenuConfig> const& GetNpcMenus() const { return _arkNpcMenuStore; }
    std::string GetItemNameByEntry(Player* player, uint32 entry, bool showchat = false) const;

    bool CheckNullBag(Player* player, uint32 itemId, uint32 count);
    bool AddItem(Player* player, uint32 itemId, uint32 count);

    //Item Enchantment
    void LoadArkItemEnchantmentDB();
    typedef std::unordered_map<uint32, ArkItemEnchantment> ArkItemEnchantmentContainer;
    ArkItemEnchantment const* GetArkItemEnchantmentConfig(uint32 itemid) const
    {
        ArkItemEnchantmentContainer::const_iterator itr = _arkItemEnchantmentStore.find(itemid);
        return itr != _arkItemEnchantmentStore.end() ? &itr->second : nullptr;
    }

    // transmogrification
    void LoadArkItemTransmog(Player* player);

    // learn class trainer
    void LearnTrainer(Player* player, uint32 templateid);
    void LearnLevelTrainer(Player* player);

    void SetAccountRecharge(uint32 accountId);
    uint32 GetRechargejf(uint32 accountId) const;
    uint32 GetRechargeAll(uint32 accountId) const;
private:
    ArkConfigContainer _arkConfigStore;
    ArkVipSystemContainer _arkVipSystemStore;
    ArkInstanceContainer _arkInstanceStore;
    ArkNpcMenuContainer _arkNpcMenuStore;
    ArkItemEnchantmentContainer _arkItemEnchantmentStore;
};

#define sArkMgr MaNGOS::Singleton<ArkMgr>::Instance()

#endif
