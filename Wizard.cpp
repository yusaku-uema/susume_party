#include"DxLib.h"
#include"Wizard.h"

Wizard::Wizard() : PlayerBase()
{
	if (LoadDivGraph("image/Player/wizard.png", 4, 4, 1, 24, 24, player_image) == -1)throw("image/Player/wizard.pngが読み込めません\n");
}

Wizard::~Wizard()
{

}