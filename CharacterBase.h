#pragma once
#include"BoxCollider.h"

class CharacterBase : public BoxCollider
{
protected:
    class Stage* stage;
    class PlayerManager* player_manager;
    class EnemyManager* enemy_manager;
    class AttackManager* attack_manager;

    DATA speed;//スピード

    bool is_facing_left; //左を向いているか？

public:
    CharacterBase(DATA location, DATA size);
    ~CharacterBase();

    void SetPointer(class Stage* stage, class PlayerManager* player_manager, class EnemyManager* enemy_manager, class AttackManager* attack_manager);
};