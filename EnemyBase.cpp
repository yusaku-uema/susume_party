#include "EnemyBase.h"

EnemyBase::EnemyBase():CharacterBase({ 1400.0f, 50.0f }, { 50, 50 }, 20, 10, 5, 5)
{

}

bool EnemyBase::HitDamege(int attack_power)
{
    if ((hp -= attack_power) <= 0)
    {
        hp = 0;
        return true;
    }
    return false;
}

EnemyBase::~EnemyBase()
{

}
