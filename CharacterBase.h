#pragma once
#include"BoxCollider.h"

class CharacterBase : public BoxCollider
{
protected:
    class Stage* stage;
    class PlayerManager* player_manager;
    class EnemyManager* enemy_manager;
    class AttackManager* attack_manager;

    int hp;
    int mp;
    int attack_power;//�U����
    int defense_power;//�����

    DATA speed;//�X�s�[�h
public:
    CharacterBase(DATA location, DATA size, int hp, int mp, int attack_power, int defense_power);
    ~CharacterBase();

    int GetAttackPower()const;
    int GetDefensePower()const;
    int GetHp()const;
    int GetMp()const;
};