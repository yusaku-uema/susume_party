#include"DxLib.h"
#include "EnemyBase.h"

EnemyBase::EnemyBase():CharacterBase({ 1400.0f, 50.0f }, { 50, 50 }, 20, 10, 5, 5)
{
    OutputDebugString("EnemyBase�R���X�g���N�^�Ă΂�܂����B\n");
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
    OutputDebugString("EnemyBase�f�X�g���N�^�Ă΂�܂����B\n");
}
