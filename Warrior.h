#pragma once
#include"PlayerBase.h"

class Warrior : public PlayerBase
{
private:

public:
    Warrior(class Stage* stage, class PlayerManager* player_manager, class EnemyManager* enemy_manager, class AttackManager* attack_manager);
    ~Warrior();
};