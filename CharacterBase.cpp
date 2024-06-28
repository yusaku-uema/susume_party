#include"DxLib.h"
#include"CharacterBase.h"

CharacterBase::CharacterBase(DATA location, DATA size) : BoxCollider(location, size),
speed({ 0.0f,0.0f }), is_facing_left(true), image_change_time(0.0f), draw_image_num(0)
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


//-----------------------------------
//キャラクター間の距離を測る
//-----------------------------------
float CharacterBase::CalculateDistance(class BoxCollider* character)const
{
    float dx = character->GetLocation().x - this->GetLocation().x;
    float dy = character->GetLocation().y - this->GetLocation().y;
    float distance = sqrt(dx * dx + dy * dy); // ユークリッド距離の計算（平方根を取る）

    return distance;
}

