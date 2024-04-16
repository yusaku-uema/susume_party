#include"DxLib.h"
#include"Block.h"

Block::Block(DATA location, BLOCK_TYPE type, int block_image) : BoxCollider(location, { BLOCK_SIZE, BLOCK_SIZE }),
type(type), block_image(block_image)
{
	OutputDebugString("Blockコンストラクタが呼ばれました。\n");
}

Block::~Block()
{
	OutputDebugString("Blockデストラクタが呼ばれました。\n");
}

void Block::Draw()const
{
	DrawRotaGraph(location.x, location.y, 1, 0, block_image, FALSE);
}

BLOCK_TYPE Block::GetType()const//ブロックタイプを返す
{
	return type;
}