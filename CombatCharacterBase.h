#pragma once
#include"CharacterBase.h"

class CombatCharacterBase : public CharacterBase
{
protected:
    int hp;//UŒ‚—Í
    int mp;//–‚–@—Í
    int attack_power;//UŒ‚—Í
    int defense_power;//ç”õ—Í

    bool is_dead;//€‚ñ‚Å‚¢‚é‚©H

public:
    CombatCharacterBase(DATA location, DATA size, int hp, int mp, int attack_power, int defense_power);
    ~CombatCharacterBase();

    //UŒ‚‚ğH‚ç‚Á‚½‚Ìˆ—
    virtual bool HitDamege(BoxCollider* bc, int attack_power) { return false; }

    int GetHp()const;
    int GetMp()const;
    bool GetIsDead()const;
};