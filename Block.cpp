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

void Block::Draw(float camera_work)const
{
	DATA draw_location = { location.x + camera_work, location.y };

	if ((draw_location.x >= -radius.x) && (draw_location.x <= SCREEN_WIDTH + radius.x))//��ʓ��Ƀu���b�N������ꍇ
	{
		DrawRotaGraph(draw_location.x, draw_location.y, 1, 0, block_image, FALSE);
		//DrawBox(draw_location.x - radius.x, draw_location.y - radius.y, draw_location.x + radius.x, draw_location.y + radius.y, 0xffffff, TRUE);
		DrawBox(draw_location.x - radius.x, draw_location.y - radius.y, draw_location.x + radius.x, draw_location.y + radius.y, 0x000000, FALSE);

	}
}

BLOCK_TYPE Block::GetType()const//�u���b�N�^�C�v��Ԃ�
{
	return type;
}