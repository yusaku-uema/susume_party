#include"TitleScene.h"
#include"DxLib.h"
#include"Key.h"

TitleScene::TitleScene()
{
 
}

TitleScene::~TitleScene()
{
}

//初期化処理
void TitleScene::Initialize()
{
}

void TitleScene::Finalize()
{
}

//更新処理
SCENE_TYPE TitleScene::Update(float delta_time)
{
	if (Key::KeyDown(KEY_TYPE::A))return SCENE_TYPE::MAIN;
    return GetNowScene();//現在のシーンタイプを返す
}

//描画処理
void TitleScene::Draw() const
{
	DrawString(0, 0, "タイトル", 0xffffff);
}

//現在のシーン情報を取得
SCENE_TYPE TitleScene::GetNowScene() const
{
	return SCENE_TYPE::TITLE;
}

