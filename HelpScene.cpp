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

}

void HelpScene::Finalize()
{



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
	

	

	DrawString(0, 0, "help", 0xffffff);
}

SCENE_TYPE HelpScene::GetNowScene() const
{
	return SCENE_TYPE::HELPSCENE;
}
