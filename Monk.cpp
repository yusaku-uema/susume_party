#include"DxLib.h"
#include"Monk.h"

Monk::Monk(class Stage* stage) : PlayerBase(stage, PLAYER_JOB::MONK)
{
	if (LoadDivGraph("image/Player/Monk/walk.png", 5, 5, 1, 50, 50, player_image[0]) == -1)throw("image/Player/Monk/walk.pngが読み込めません\n");
	if (LoadDivGraph("image/Player/Monk/wait.png", 5, 5, 1, 50, 50, player_image[1]) == -1)throw("image/Player/Monk/wait.pngが読み込めません\n");
}

Monk::~Monk()
{

}