#include "Fairy.h"
#define FAIRY_SIZE 64


//-----------------------------------
//コンストラクタ
//-----------------------------------
Fairy::Fairy() : CharacterBase({ 1400.0f, 50.0f }, { FAIRY_SIZE, FAIRY_SIZE }, 20, 10, 5, 5)
{

}


//-----------------------------------
//デストラクタ
//-----------------------------------
Fairy::~Fairy()
{

}


//-----------------------------------
//更新処理
//-----------------------------------
void Fairy::Update(float delta_time, Stage* stage, PlayerManager* player)
{

}


//-----------------------------------
//描画
//-----------------------------------
void Fairy::Draw(float camera_work) const
{

}


//-----------------------------------
//移動
//-----------------------------------
void Fairy::Move(Stage* stage, PlayerManager* player)
{

}


//-----------------------------------
//待機
//-----------------------------------
void Fairy::Standby(PlayerManager* player)
{

}


//-----------------------------------
//攻撃
//-----------------------------------
void Fairy::Attack(Stage* stage, PlayerManager* player, float delta_time)
{

}


//-----------------------------------
//相手との距離を測る
//-----------------------------------
float Fairy::CalculateDistance(PlayerManager* player)
{
	return 0.0f;
}
