#include"DxLib.h"
#include"Monk.h"

Monk::Monk(class Stage* stage, class PlayerManager* player_manager, class AttackManager* attack_manager) : PlayerBase(PLAYER_JOB::MONK)
{
	this->stage = stage;
	this->player_manager = player_manager;
	this->attack_manager = attack_manager;

	if (LoadDivGraph("image/Player/Monk/walk.png", 5, 5, 1, 50, 50, player_image[0]) == -1)throw("image/Player/Monk/walk.png‚ª“Ç‚İ‚ß‚Ü‚¹‚ñ\n");
	if (LoadDivGraph("image/Player/Monk/wait.png", 5, 5, 1, 50, 50, player_image[1]) == -1)throw("image/Player/Monk/wait.png‚ª“Ç‚İ‚ß‚Ü‚¹‚ñ\n");
}

Monk::~Monk()
{

}