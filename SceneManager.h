#pragma once
#include"SceneBase.h"

#define FREAM_RATE (30)//フレームレート
#define DELTA_SECOND  (1000 / FREAM_RATE)//1フレーム当たりの時間

class SceneManager//シーンマネージャークラス
{
private:
	SceneBase* current_scene;   //現在シーン

public:
	SceneManager() ;
	~SceneManager();

	void Initialize();  //初期化処理
	void Finalize();    //終了時処理
	void Update() ;      //更新処理
	

private:
	void Draw() const;   //描画処理
	void ChangeScene(SCENE_TYPE scene_type);  //シーン切り替え処理
	SceneBase* CreateScene(SCENE_TYPE scene_type); //シーン生成処理
};