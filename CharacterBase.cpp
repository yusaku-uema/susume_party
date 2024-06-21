#include"DxLib.h"
#include"CharacterBase.h"

CharacterBase::CharacterBase(DATA location, DATA size, int hp, int mp, int attack_power, int defense_power) : BoxCollider(location, size),
hp(hp), mp(mp), attack_power(attack_power), defense_power(defense_power), speed({ 0.0f,0.0f }), is_dead(false)
{
    OutputDebugString("CharacterBaseコンストラクタ呼ばれました。\n");
}

void CharacterBase::SetPointer(class Stage* stage, class PlayerManager* player_manager, class EnemyManager* enemy_manager, class AttackManager* attack_manager)
{
    this->stage = stage;
    this->player_manager = player_manager;
    this->enemy_manager = enemy_manager;
    this->attack_manager = attack_manager;
}

CharacterBase::~CharacterBase()
{
    OutputDebugString("CharacterBaseデストラクタが呼ばれました。\n");
}

int CharacterBase::GetHp()const
{
    return hp;
}

int CharacterBase::GetMp()const
{
    return mp;
}

bool CharacterBase::GetIsDead()const
{
    return is_dead;
}