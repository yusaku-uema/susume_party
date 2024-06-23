#pragma once
#include"PlayerBase.h"

class Monk : public PlayerBase
{
private:

public:
    Monk(class Stage* stage, class PlayerManager* player_manager, class EnemyManager* enemy_manager, class AttackManager* attack_manager);
    ~Monk();
};