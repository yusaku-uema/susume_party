#include "CreditScene.h"
#include "DxLib.h"
#include "Key.h"

CreditScene::CreditScene()
{


}

CreditScene::~CreditScene()
{
}

void CreditScene::Initialize()
{

}

void CreditScene::Finalize()
{



}

SCENE_TYPE CreditScene::Update(float delta_time)
{
	if (Key::KeyDown(KEY_TYPE::B))
	{
		return SCENE_TYPE::TITLE;
	}



	return GetNowScene();
}

void CreditScene::Draw() const
{




	DrawString(0, 0, "Credit", 0xffffff);
	

	DrawString(500, 200, "MusMus \n DOVA-SYNDROME", 0xfffff);


}

SCENE_TYPE CreditScene::GetNowScene() const
{
	return SCENE_TYPE::CREDITSCENE;
}
