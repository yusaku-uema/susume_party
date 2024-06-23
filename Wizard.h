#pragma once
#include"PlayerBase.h"

class Wizard : public PlayerBase
{
private:
    void SpecialSkill()override;
public:
    Wizard(class Stage* stage, class PlayerManager* player_manager, class EnemyManager* enemy_manager, class AttackManager* attack_manager);
    ~Wizard();
};