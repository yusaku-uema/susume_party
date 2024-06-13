#pragma once
#include "SceneBase.h"

#define MENU_NUM 4

class TitleScene :public SceneBase
{
private:
	int image;//ƒ^ƒCƒgƒ‹‰æ‘œ
	int menu_image[MENU_NUM][2];
	int num_image[4];
	int set_menu_image[8];

	int input_time;
	int select_menu;
	int help_menu;

	bool help;
	bool credit;

public:
	TitleScene();
	virtual ~TitleScene();

	virtual void Initialize() override;
	virtual void Finalize() override;

	virtual SCENE_TYPE Update(float delta_time) override;
	virtual void Draw() const override;

	virtual SCENE_TYPE GetNowScene() const override;
};