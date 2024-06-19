#pragma once
#include "SceneBase.h"


class HelpScene : public SceneBase
{
public:
    HelpScene();
    ~HelpScene();

    void Initialize() override;
    void Finalize() override;
    SCENE_TYPE Update(float delta_time) override;
    void Draw() const override;
    SCENE_TYPE GetNowScene() const override;

   

private:
   
    int help_image;//ƒwƒ‹ƒv‰æ‘œ

};


