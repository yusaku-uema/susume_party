#include"GameOverScene.h"
#include"Key.h"
#include"DxLib.h"

GameOverScene::GameOverScene()
{
}

GameOverScene::~GameOverScene()
{
}

//初期化処理
void GameOverScene::Initialize()
{
}

//終了時処理
void GameOverScene::Finalize()
{
}

//更新処理
SCENE_TYPE GameOverScene::Update(float delta_time)
{
	if (Key::KeyDown(KEY_TYPE::A))return SCENE_TYPE::MAIN;
	return GetNowScene();
}

//描画処理
void GameOverScene::Draw() const
{
	DrawString(0, 0, "ゲームオーバー", 0xffffff);
}


//現在のシーン情報を取得
SCENE_TYPE GameOverScene::GetNowScene() const
{
	return SCENE_TYPE::GAME_OVER;
}