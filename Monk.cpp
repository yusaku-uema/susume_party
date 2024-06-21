#include"DxLib.h"
#include"Monk.h"

Monk::Monk() : PlayerBase(PLAYER_JOB::MONK)
{
	if (LoadDivGraph("image/Player/Monk/walk.png", 5, 5, 1, 50, 50, player_image[0]) == -1)throw("image/Player/Monk/walk.png‚ª“Ç‚İ‚ß‚Ü‚¹‚ñ\n");
	if (LoadDivGraph("image/Player/Monk/wait.png", 5, 5, 1, 50, 50, player_image[1]) == -1)throw("image/Player/Monk/wait.png‚ª“Ç‚İ‚ß‚Ü‚¹‚ñ\n");
	if ((weapon_image = LoadGraph("image/Player/Monk/weapon.png")) == -1)throw("image/Player/Monk/weapon.png‚ª“Ç‚İ‚ß‚Ü‚¹‚ñ\n");
}

Monk::~Monk()
{

}