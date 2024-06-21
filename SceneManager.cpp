#include"DxLib.h"
#include"SceneManager.h"
#include"TitleScene.h"
#include"TalkUi.h"
#include"HelpScene.h"
#include"CreditScene.h"
#include"GameMainScene.h"
#include"GameOverScene.h"
#include"GameClearScene.h"
#include"Key.h"


SceneManager::SceneManager() : current_scene(nullptr)
{
}

SceneManager::~SceneManager()
{	
}

//シーンマネジャー機能:初期化処理
void SceneManager::Initialize()
{

	SetWindowIconID(01);

	//ウィンドウのタイトルを設定
	SetMainWindowText("進め!!パーティ");

	//ウィンドウモードで起動
	if (ChangeWindowMode(TRUE) != DX_CHANGESCREEN_OK)
	{
		throw("ウィンドウモードで起動できませんでした\n");
	}

	SetGraphMode(1280, 720, 32);

	//DXライブラリの初期化
	if (DxLib_Init() == -1)
	{
		throw("Dxライブラリが初期化できませんでした\n");
	}

	//描画先指定処理
	if (SetDrawScreen(DX_SCREEN_BACK) == -1)
	{
		throw("描画先の指定ができませんでした\n");
	}

	//タイトルシーンから始める
	ChangeScene(SCENE_TYPE::MAIN);
}

//シーンマネージャー機能:更新処理
void SceneManager::Update()
{
	int delta_second = 1000 / 60;
	int delta_time = 0.0f;

	while (ProcessMessage() != -1)//メインループ
	{
		int start_time = GetNowCount();

		// 入力更新
		Key::Update();

		//更新処理
		SCENE_TYPE next_scene = current_scene->Update((float)delta_time / 1000);

		//エンドが選択されていたらゲームを終了する
		if (next_scene == SCENE_TYPE::GAME_END)break;

		//現在のシーンと次のシーンが違っていたらシーンを変える
		if (next_scene != current_scene->GetNowScene())ChangeScene(next_scene);

		//描画処理
		Draw();

		if (delta_second > (GetNowCount() - start_time))WaitTimer(delta_second - (GetNowCount() - start_time));
		delta_time = GetNowCount() - start_time;
	}
}

//シーンマネージャー機能：終了時処理
void SceneManager::Finalize()
{
	//シーン情報の削除
	if (current_scene != nullptr)
	{
		current_scene->Finalize();
		delete current_scene;
		current_scene = nullptr;
	}

	//DXライブラリの使用を終了する
	DxLib_End();
}

//シーンマネージャー機能：描画処理
void SceneManager::Draw() const
{
	ClearDrawScreen();//画面の初期化

	current_scene->Draw();//シーンの描画

	ScreenFlip();//裏画面の内容を表画面に反映
}

void SceneManager::ChangeScene(SCENE_TYPE scene_type)//シーン切り替え処理
{
	//シーンを生成する
	SceneBase* new_scene = CreateScene(scene_type);

	if (new_scene == nullptr)throw("シーンが生成できませんでした。\n");//エラーチェック
	
	if (current_scene != nullptr)//前回シーンの終了時処理を行う
	{
		current_scene->Finalize();
		delete current_scene;
	}

	new_scene->Initialize();//新しく生成したシーンの初期化を行う

	current_scene = new_scene;//現在のシーンの更新(入れ替え)
}

//シーン生成処理
SceneBase* SceneManager::CreateScene(SCENE_TYPE scene_type)
{
	//引数（シーンタイプ）によって、生成するシーンを決定する
	switch (scene_type)
	{
	case SCENE_TYPE::TITLE:
		return new TitleScene;
	case SCENE_TYPE::TALKUI:
		return new TalkUi;
	case SCENE_TYPE::HELPSCENE:
		return new HelpScene;
	case SCENE_TYPE::CREDITSCENE:
		return new CreditScene;
	case SCENE_TYPE::MAIN:
		return new GameMainScene;
	case SCENE_TYPE::GAME_OVER:
		return new GameOverScene;
	case SCENE_TYPE::GAME_CLEAR:
		return new GameClearScene;
	case SCENE_TYPE::ENDING:
	default:
		return nullptr;
	}
}