#include"DxLib.h"
#include"Hero.h"

Hero::Hero() : PlayerBase()
{
	if (LoadDivGraph("image/Player/hero.png", 4, 4, 1, 24, 24, player_image) == -1)throw("image/Player/hero.png���ǂݍ��߂܂���\n");
}

Hero::~Hero()
{

}