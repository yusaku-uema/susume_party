#include"DxLib.h"
#include"Stage.h"

Stage::Stage()
{
	player = new Player();
	
	OutputDebugString("Stage�R���X�g���N�^�Ă΂�܂����B\n");
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

	OutputDebugString("Stage�f�X�g���N�^�Ă΂�܂����B\n");
}

void Stage::Update(float delta_time)
{
}

bool Stage::HitBlock(BoxCollider* bc)const
{
	for (int i = 0; i < block.size(); i++)if (block[i].HitBox(bc))return true;//�u���b�N�ɓ��������ꍇtrue��Ԃ�
	return false;//�u���b�N�ɓ�����Ȃ�����
}

void Stage::Draw() const
{
}