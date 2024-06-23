#pragma once
#include"SceneBase.h"
#include"Stage.h"

class GameMainScene :public SceneBase
{
private:

	Stage* stage;
	
	int bgm;
	bool is_pause;//ポーズ画面表示するか？

public:
	GameMainScene();
	virtual ~GameMainScene();

	void Initialize() override;
	void Finalize() override;

	virtual SCENE_TYPE Update(float delta_time) override;
	virtual void Draw() const override;
	
	virtual SCENE_TYPE GetNowScene() const override;
};