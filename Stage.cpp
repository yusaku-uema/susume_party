#include"DxLib.h"
#include"Stage.h"

Stage::Stage()
{
	player = new Player();
	
	OutputDebugString("Stageコンストラクタ呼ばれました。\n");
}

void Stage::SetStage()
{
}

void Stage::Initialize()
{
}

Stage::~Stage()
{
	delete player;

	OutputDebugString("Stageデストラクタ呼ばれました。\n");
}

void Stage::Update(float delta_time)
{
}

bool Stage::HitBlock(BoxCollider* bc)const
{
	for (int i = 0; i < block.size(); i++)if (block[i].HitBox(bc))return true;//ブロックに当たった場合trueを返す
	return false;//ブロックに当たらなかった
}

void Stage::Draw() const
{
}