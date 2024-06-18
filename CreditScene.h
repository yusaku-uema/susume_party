#pragma once
#include "SceneBase.h"


class CreditScene : public SceneBase
{
public:
    CreditScene();
    ~CreditScene();

    void Initialize() override;
    void Finalize() override;
    SCENE_TYPE Update(float delta_time) override;
    void Draw() const override;
    SCENE_TYPE GetNowScene() const override;



private:



};


