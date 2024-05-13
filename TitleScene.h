#pragma once
#include "SceneBase.h"

class TitleScene :public SceneBase
{
private:

public:
	TitleScene();
	virtual ~TitleScene();

	virtual void Initialize() override;
	virtual void Finalize() override;

	virtual SCENE_TYPE Update(float delta_time) override;
	virtual void Draw() const override;

	virtual SCENE_TYPE GetNowScene() const override;
};