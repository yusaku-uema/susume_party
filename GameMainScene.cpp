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
	ui = new Ui();
	stage = new Stage(ui);
	message = new Message("txt/comment.txt");
	bgm= LoadSoundMem("bgm/stage.mp3");
}

//終了時処理
void GameMainScene::Finalize()
{
	delete ui;
	delete stage;
	delete message;

	StopSoundMem(bgm);
	DeleteSoundMem(bgm);
}

//更新処理
SCENE_TYPE GameMainScene::Update(float delta_time)
{

	if (CheckSoundMem(bgm) != 1)
	{   //SEが流れていなかったら再生
		PlaySoundMem(bgm, DX_PLAYTYPE_BACK, TRUE); //SE再生
	}


	ui->Update();

	// ステージの更新処理
	if (stage->Update(delta_time))return SCENE_TYPE::GAME_OVER;

	if (stage->NextTransition()) return SCENE_TYPE::GAME_CLEAR;

	// メッセージの更新処理
	if (message != nullptr)
	{
		if (message->Update(delta_time))
		{
			delete message;
			message = nullptr;
		}
	}

	if ((this->delta_time += delta_time) >= 1.0f)
	{
		this->delta_time = 0.0f;
		fps = fps_count;
		fps_count = 0;
	}
	else fps_count++;

	return GetNowScene();
}

//描画処理
void GameMainScene::Draw() const
{
	stage->Draw();

	ui->Draw();

	//if(message != nullptr)message->Draw();

	DrawFormatString(500, 0, 0xffffff, "%d", fps);
}

//現在のシーン情報を取得
SCENE_TYPE GameMainScene::GetNowScene() const
{
	return SCENE_TYPE::MAIN;
}