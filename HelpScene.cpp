#include "HelpScene.h"
#include "DxLib.h"
#include "Key.h"

HelpScene::HelpScene()
{

	
}

HelpScene::~HelpScene()
{
}

void HelpScene::Initialize()
{
	help_image = LoadGraph("image/Help/Help.png");
	if (help_image == -1)
	{
		throw("image/Help/help.pngÇ™ì«Ç›çûÇﬂÇ‹ÇπÇÒ\n");
	}

}

void HelpScene::Finalize()
{

	DeleteGraph(help_image);

}

SCENE_TYPE HelpScene::Update(float delta_time)
{
	if (Key::KeyDown(KEY_TYPE::B))
	{
		return SCENE_TYPE::TITLE;
	}



	return GetNowScene();
}

void HelpScene::Draw() const
{
	


	DrawGraph(0, 0, help_image, TRUE);

	//DrawString(0, 0, "help", 0xffffff);
}

SCENE_TYPE HelpScene::GetNowScene() const
{
	return SCENE_TYPE::HELPSCENE;
}
