#pragma once
#include"SceneBase.h"
#include"define.h"

class GameOverScene :public SceneBase
{
private:

public:
	GameOverScene();
	virtual ~GameOverScene();

	virtual void Initialize() override;
	virtual void Finalize() override;

	virtual SCENE_TYPE Update(float delta_time) override;
	virtual void Draw() const override;

	virtual SCENE_TYPE GetNowScene() const override;
};