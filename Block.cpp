#include"DxLib.h"
#include"Block.h"

Block::Block(DATA location,int block_image) : BoxCollider(location, { BLOCK_SIZE, BLOCK_SIZE }),block_image(block_image)
{
	OutputDebugString("Blockコンストラクタが呼ばれました。\n");
}

Block::~Block()
{
	OutputDebugString("Blockデストラクタが呼ばれました。\n");
}

bool Block::Draw(float camera_work)const
{
	DATA draw_location = { location.x + camera_work, location.y };
	if (draw_location.x > (SCREEN_SIZE_X + radius.x))return true;
	if (draw_location.x >= -radius.x)DrawRotaGraph(draw_location.x, draw_location.y, 1, 0, block_image, TRUE);
	return false;
}