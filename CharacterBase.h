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
    int attack_power;//攻撃力
    int defense_power;//守備力

    bool is_dead;//死んでいるか？
    bool is_facing_left; //左を向いているか？

    DATA speed;//スピード
public:
    CharacterBase(DATA location, DATA size, int hp, int mp, int attack_power, int defense_power);
    ~CharacterBase();

    virtual bool HitDamege(BoxCollider* bc, int attack_power) { return false; }//攻撃を食らった時の処理

    int GetHp()const;
    int GetMp()const;
    bool GetIsDead()const;
};