#include"DxLib.h"
#include"Warrior.h"

Warrior::Warrior() : PlayerBase()
{
	if (LoadDivGraph("image/Player/warrior.png", 4, 4, 1, 24, 24, player_image) == -1)throw("image/Player/warrior.png���ǂݍ��߂܂���\n");
}

Warrior::~Warrior()
{

}