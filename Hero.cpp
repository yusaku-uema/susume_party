#include"DxLib.h"
#include"Hero.h"
#include"Key.h"

Hero::Hero() : PlayerBase(0xffffff)
{
	if (LoadDivGraph("image/Player/warrior.png", 4, 4, 1, 25, 32, player_image) == -1)throw("image/Player/warrior.png‚ª“Ç‚İ‚ß‚Ü‚¹‚ñ\n");
}

Hero::~Hero()
{

}