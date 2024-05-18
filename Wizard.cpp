#include"DxLib.h"
#include"Wizard.h"

Wizard::Wizard(class Stage* stage) : PlayerBase(stage, PLAYER_JOB::WIZARD)
{
	if (LoadDivGraph("image/Player/Wizard/walk.png", 5, 5, 1, 50, 50, player_image[0]) == -1)throw("image/Wizard/Hero/walk.png���ǂݍ��߂܂���\n");
	if (LoadDivGraph("image/Player/Wizard/wait.png", 5, 5, 1, 50, 50, player_image[1]) == -1)throw("image/Wizard/Hero/wait.png���ǂݍ��߂܂���\n");
}

Wizard::~Wizard()
{

}