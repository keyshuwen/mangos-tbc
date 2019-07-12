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

 /*
 * Custom training dummy script
 */

struct npc_training_dummyAI : ScriptedAI
{
    explicit npc_training_dummyAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        npc_training_dummyAI::Reset();
    }

    uint32 m_uiCombatTimer;
    std::unordered_map<ObjectGuid, time_t> attackers;

    void Reset() override
    {
        m_uiCombatTimer = 15000;
        attackers.clear();
    }

    void AttackStart(Unit* /*pWho*/) override {}

    void Aggro(Unit* pWho) override
    {
        SetCombatMovement(false);
    }

    void AddAttackerToList(Unit* pWho)
    {
        auto itr = attackers.find(pWho->GetObjectGuid());
        if (itr != attackers.end())
        {
            itr->second = std::time(nullptr);
        }
        else
        {
            attackers.emplace(pWho->GetObjectGuid(), std::time(nullptr));
        }
    }

    void DamageTaken(Unit* pWho, uint32& /*damage*/, DamageEffectType /*damagetype*/, SpellEntry const* /*spellInfo*/) override
    {
        if (pWho)
            AddAttackerToList(pWho);
    }

    void SpellHit(Unit* pWho, const SpellEntry* /*pSpell*/) override
    {
        if (pWho)
            AddAttackerToList(pWho);
    }

    void UpdateAI(const uint32 diff) override
    {
        if (m_creature->isInCombat())
        {
            if (m_uiCombatTimer <= diff)
            {
                for (auto itr = attackers.begin(); itr != attackers.end();)
                {
                    Unit* pAttacker = m_creature->GetMap()->GetUnit(itr->first);

                    if (!pAttacker || !pAttacker->IsInWorld())
                    {
                        itr = attackers.erase(itr);
                        continue;
                    }
                    if (itr->second + 10 < std::time(nullptr))
                    {
                        m_creature->_removeAttacker(pAttacker);
                        m_creature->getThreatManager().modifyThreatPercent(pAttacker, -101.0f);
                        itr = attackers.erase(itr);
                        continue;
                    }
                    ++itr;
                }

                m_creature->ModifyHealth(m_creature->GetMaxHealth());

                if (m_creature->getThreatManager().isThreatListEmpty())
                    EnterEvadeMode();

                m_uiCombatTimer = 15000;
            }
            else
                m_uiCombatTimer -= diff;
        }
    }
};

UnitAI* GetAI_npc_training_dummy(Creature* pCreature)
{
    return new npc_training_dummyAI(pCreature);
}

void AddSC_ark_npc_training_dummy()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "ark_npc_training_dummy";
    pNewScript->GetAI = &GetAI_npc_training_dummy;
    pNewScript->RegisterSelf(false);
}
