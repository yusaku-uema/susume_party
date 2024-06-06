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

    bool is_dead;//����ł��邩�H
    bool is_facing_left; //���������Ă��邩�H

    DATA speed;//�X�s�[�h
public:
    CharacterBase(DATA location, DATA size, int hp, int mp, int attack_power, int defense_power);
    ~CharacterBase();

    virtual bool HitDamege(BoxCollider* bc, int attack_power) { return false; }//�U����H��������̏���

    int GetHp()const;
    int GetMp()const;
    bool GetIsDead()const;
};