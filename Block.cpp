#include"DxLib.h"
#include"Block.h"

Block::Block(DATA location, BLOCK_TYPE type, int block_image) : BoxCollider(location, { BLOCK_SIZE, BLOCK_SIZE }),
type(type), block_image(block_image)
{
	OutputDebugString("Block�R���X�g���N�^���Ă΂�܂����B\n");
}

Block::~Block()
{
	OutputDebugString("Block�f�X�g���N�^���Ă΂�܂����B\n");
}

void Block::Draw()const
{
	DrawRotaGraph(location.x, location.y, 1, 0, block_image, FALSE);
}

BLOCK_TYPE Block::GetType()const//�u���b�N�^�C�v��Ԃ�
{
	return type;
}