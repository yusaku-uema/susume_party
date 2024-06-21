#pragma once

//シーン情報
enum SCENE_TYPE
{
	TITLE,
	TALKUI,
	HELPSCENE,
	CREDITSCENE,
	MAIN,
	GAME_OVER,
	GAME_CLEAR,
	ENDING,
	GAME_END
};

//基底シーンクラス
class SceneBase
{
public:
	SceneBase(){}
	virtual ~SceneBase(){}

	//初期化処理
	virtual void Initialize(){}
	//更新処理
	virtual SCENE_TYPE Update(float delta_time)
	{
		return GetNowScene();
	}
	//描画処理
	virtual void Draw() const{}
	//終了時処理
	virtual void Finalize(){}

	//現在のシーン情報を取得
	virtual SCENE_TYPE GetNowScene() const = 0;
};