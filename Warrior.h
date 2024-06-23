#pragma once
#include"PlayerBase.h"

class Warrior : public PlayerBase
{
private:

public:
    Warrior(DATA location, class Stage* stage, class PlayerManager* player_manager, class EnemyManager* enemy_manager, class AttackManager* attack_manager);
    ~Warrior();

    void SpecialSkill()override;
};