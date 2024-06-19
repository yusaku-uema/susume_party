#pragma once
#include "SceneBase.h"
#include"Message.h"

class TalkUi : public SceneBase
{
public:
    TalkUi();
    ~TalkUi();

    void Initialize() override;
    void Finalize() override;
    SCENE_TYPE Update(float delta_time) override;
    void Draw() const override;
    SCENE_TYPE GetNowScene() const override;

    Message* message; // メッセージ表示用のインスタンス

private:
    int king_image;//王様
    int background_image;//背景


};


    