#include"DxLib.h"
#include"Monk.h"

Monk::Monk() : PlayerBase()
{
	if (LoadDivGraph("image/Player/monk.png", 4, 4, 1, 24, 24, player_image) == -1)throw("image/Player/monk.pngが読み込めません\n");
}

Monk::~Monk()
{

}