#include"DxLib.h"
#include"Hero.h"

Hero::Hero(class Stage* stage) : PlayerBase(stage)
{
	if (LoadDivGraph("image/Player/Hero/walk.png", 5, 5, 1, 50, 50, player_image[0]) == -1)throw("image/Player/Hero/walk.png���ǂݍ��߂܂���\n");
	if (LoadDivGraph("image/Player/Hero/wait.png", 5, 5, 1, 50, 50, player_image[1]) == -1)throw("image/Player/Hero/wait.png���ǂݍ��߂܂���\n");
}

Hero::~Hero()
{

}