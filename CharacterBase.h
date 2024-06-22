#pragma once
#include"BoxCollider.h"

class CharacterBase : public BoxCollider
{
protected:
    class Stage* stage;
    class PlayerManager* player_manager;
    class EnemyManager* enemy_manager;
    class AttackManager* attack_manager;

    DATA speed;//�X�s�[�h

    bool is_facing_left; //���������Ă��邩�H

public:
    CharacterBase(DATA location, DATA size);
    ~CharacterBase();

    void SetPointer(class Stage* stage, class PlayerManager* player_manager, class EnemyManager* enemy_manager, class AttackManager* attack_manager);
};