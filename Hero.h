#pragma once
#include"PlayerBase.h"

class Hero : public PlayerBase
{
private:
    void SpecialSkill()override;
public:
    Hero(DATA location, class Stage* stage, class PlayerManager* player_manager, class EnemyManager* enemy_manager, class AttackManager* attack_manager);
    ~Hero();
};