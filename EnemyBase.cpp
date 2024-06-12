#include"DxLib.h"
#include "EnemyBase.h"

EnemyBase::EnemyBase():CharacterBase({ 1400.0f, 50.0f }, { 50, 50 }, 20, 10, 5, 5)
{
    OutputDebugString("EnemyBaseコンストラクタ呼ばれました。\n");
    death_animation = false;
    if (LoadDivGraph("image/Effect/fireball.png", 4, 4, 1, 24, 24, death_effects) == -1)throw("死亡エフェクト\n");
}

bool EnemyBase::HitDamege(BoxCollider* bc, int attack_power)
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
    OutputDebugString("EnemyBaseデストラクタ呼ばれました。\n");
    for (int i = 0; i < 4; i++)
    {
        DeleteGraph(death_effects[i]);
    }
  
}
