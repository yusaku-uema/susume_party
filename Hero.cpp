#include"DxLib.h"
#include"Hero.h"

Hero::Hero() : PlayerBase()
{
	if (LoadDivGraph("image/Player/hero.png", 4, 4, 1, 24, 24, player_image) == -1)throw("image/Player/hero.png‚ª“Ç‚İ‚ß‚Ü‚¹‚ñ\n");
}

Hero::~Hero()
{

}