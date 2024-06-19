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

    Message* message; // ���b�Z�[�W�\���p�̃C���X�^���X

private:
    int king_image;//���l
    int background_image;//�w�i


};


    