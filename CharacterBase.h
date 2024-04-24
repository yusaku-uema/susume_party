#pragma once
#include"BoxCollider.h"

class CharacterBase : public BoxCollider
{
protected:
    int hp;//
    int mp;//
    int attack_power;//�U����
    int defense_power;//�����

    DATA speed;//�X�s�[�h
public:
    CharacterBase(DATA location, DATA size, int hp, int mp, int attack_power, int defense_power);
    ~CharacterBase();

    int GetAttackPower()const;
    int GetDefensePower()const;
};