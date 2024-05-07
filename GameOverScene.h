#pragma once
#include"SceneBase.h"
#include"define.h"

class GameOverScene :public SceneBase
{
private:

	
	char text[256];
	bool flag;
	int FileHandle;
	int count = 0;
	int draw_x = 300;
	int draw_y = 450;
	
public:
	GameOverScene();
	virtual ~GameOverScene();

	virtual void Initialize() override;
	virtual void Finalize() override;

	void talk(int x, int y, const char t[], int nCount);
	virtual SCENE_TYPE Update(float delta_time) override;
	virtual void Draw() const override;

	virtual SCENE_TYPE GetNowScene() const override;
};