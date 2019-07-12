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
#include "Time.h"
#include "Errors.h"
#include "Log.h"
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
private:
    ArkConfigContainer _arkConfigStore;
    ArkVipSystemContainer _arkVipSystemStore;

};

#define sArkMgr MaNGOS::Singleton<ArkMgr>::Instance()

#endif
