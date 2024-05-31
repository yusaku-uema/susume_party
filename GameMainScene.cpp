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
	ui = new Ui();
	stage = new Stage(ui);
	message = new Message("txt/comment.txt");
}

//終了時処理
void GameMainScene::Finalize()
{
	delete ui;
	delete stage;
	delete message;
}

//更新処理
SCENE_TYPE GameMainScene::Update(float delta_time)
{
	ui->Update();

	stage->Update(delta_time);

	////デバック？
	//if (stage->Update(delta_time))return SCENE_TYPE::GAME_OVER;
		
	if (message != nullptr)
	{
		if (message->Update(delta_time))
		{
			delete message;
			message = nullptr;
		}
	}

	return GetNowScene();
}

//描画処理
void GameMainScene::Draw() const
{
	stage->Draw();

	ui->Draw();

	if(message != nullptr)message->Draw();
}

//現在のシーン情報を取得
SCENE_TYPE GameMainScene::GetNowScene() const
{
	return SCENE_TYPE::MAIN;
}