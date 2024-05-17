#include"GameMainScene.h"
#include"Key.h"
#include"DxLib.h"

GameMainScene::GameMainScene() : stage(nullptr),is_pause(false)
{
}

GameMainScene::~GameMainScene()
{
}

//初期化処理
void GameMainScene::Initialize()
{
	stage = new Stage();
}

//終了時処理
void GameMainScene::Finalize()
{
	delete stage;
}

//更新処理
SCENE_TYPE GameMainScene::Update(float delta_time)
{
	stage->Update(delta_time);

	return GetNowScene();
}

//描画処理
void GameMainScene::Draw() const
{
	stage->Draw();

	//画面下のUI（仮）
	DrawBox(0, 540, 1280, 720, 0x000000, TRUE);
	DrawBox(0, 540, 1280, 720, 0xffffff, FALSE);
}

//現在のシーン情報を取得
SCENE_TYPE GameMainScene::GetNowScene() const
{
	return SCENE_TYPE::MAIN;
}