#pragma once
#include"SceneBase.h"
#include"Stage.h"

class GameMainScene :public SceneBase
{
private:

	Stage* stage;
	
	int bgm;
	bool is_pause;//�|�[�Y��ʕ\�����邩�H

public:
	GameMainScene();
	virtual ~GameMainScene();

	void Initialize() override;
	void Finalize() override;

	virtual SCENE_TYPE Update(float delta_time) override;
	virtual void Draw() const override;
	
	virtual SCENE_TYPE GetNowScene() const override;
};