#include"DxLib.h"
#include"CharacterBase.h"

CharacterBase::CharacterBase(DATA location, DATA size, int hp, int mp, int attack_power, int defense_power) : BoxCollider(location, size),
hp(hp), mp(mp), attack_power(attack_power), defense_power(defense_power), speed({ 0.0f,0.0f })
{
    OutputDebugString("CharacterBaseコンストラクタ呼ばれました。\n");
}

CharacterBase::~CharacterBase()
{
    OutputDebugString("CharacterBaseデストラクタが呼ばれました。\n");
}

int CharacterBase::GetAttackPower()const
{
    return attack_power;
}

int CharacterBase::GetDefensePower()const
{
    return defense_power;
}