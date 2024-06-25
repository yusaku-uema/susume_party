#include"GameMainScene.h"
#include"Key.h"
#include"DxLib.h"

GameMainScene::GameMainScene() : stage(nullptr), is_pause(false)
{
}

GameMainScene::~GameMainScene()
{
}

//初期化処理
void GameMainScene::Initialize()
{
	stage = new Stage();
	bgm= LoadSoundMem("bgm/stage.mp3");
	SetFontSize(FONT_SIZE);
}

//終了時処理
void GameMainScene::Finalize()
{
	delete stage;
	
	StopSoundMem(bgm);
	DeleteSoundMem(bgm);
}

//更新処理
SCENE_TYPE GameMainScene::Update(float delta_time)
{

	if (CheckSoundMem(bgm) != 1)
	{   //SEが流れていなかったら再生
		PlaySoundMem(bgm, DX_PLAYTYPE_LOOP, TRUE); //SE再生
	}

	// ステージの更新処理
	if (stage->Update(delta_time))return SCENE_TYPE::GAME_OVER;

	if (stage->NextTransition()) return SCENE_TYPE::GAME_CLEAR;

	return GetNowScene();
}

//描画処理
void GameMainScene::Draw() const
{
	stage->Draw();
}

//現在のシーン情報を取得
SCENE_TYPE GameMainScene::GetNowScene() const
{
	return SCENE_TYPE::MAIN;
}