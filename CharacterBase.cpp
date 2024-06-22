#include"DxLib.h"
#include"CharacterBase.h"

CharacterBase::CharacterBase(DATA location, DATA size) : BoxCollider(location, size),
speed({ 0.0f,0.0f })
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