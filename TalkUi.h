#pragma once
#include "SceneBase.h"
#include"Message.h"

class TalkUi : public SceneBase
{
private:

	Message* message;

	int window_image;

public:
	TalkUi();
	virtual ~TalkUi();

	virtual void Initialize() override;
	virtual void Finalize() override;

	virtual SCENE_TYPE Update(float delta_time) override;
	virtual void Draw() const override;

	virtual SCENE_TYPE GetNowScene() const override;
};