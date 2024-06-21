#pragma once
#include"SceneBase.h"
#include"Stage.h"
#include"Ui.h"
#include"Message.h"

class GameMainScene :public SceneBase
{
private:
	Stage* stage;
	Ui* ui;
	Message* message;

	float delta_time = 0.0f;
	int fps = 0;
	int fps_count = 0;
	int bgm;

	bool is_pause;//ポーズ画面表示するか？
public:
	GameMainScene();
	virtual ~GameMainScene();

	virtual void Initialize() override;
	virtual void Finalize() override;

	virtual SCENE_TYPE Update(float delta_time) override;
	virtual void Draw() const override;
	
	virtual SCENE_TYPE GetNowScene() const override;
};