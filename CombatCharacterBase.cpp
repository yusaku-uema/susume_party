#include"DxLib.h"
#include"CombatCharacterBase.h"

CombatCharacterBase::CombatCharacterBase(DATA location, DATA size, int hp, int mp, int attack_power, int defense_power) : CharacterBase(location, size),
hp(hp), mp(mp), attack_power(attack_power), defense_power(defense_power),is_dead(false)
{
    OutputDebugString("CombatCharacterBaseコンストラクタ呼ばれました。\n");
}

CombatCharacterBase::~CombatCharacterBase()
{
    OutputDebugString("CombatCharacterBaseデストラクタが呼ばれました。\n");
}

int CombatCharacterBase::GetHp()const
{
    return hp;
}

int CombatCharacterBase::GetMp()const
{
    return mp;
}

bool CombatCharacterBase::GetIsDead()const
{
    return is_dead;
}