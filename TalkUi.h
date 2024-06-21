#pragma once
#include "SceneBase.h"
#include "Message.h"

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
    int king_image; // ���l�̉摜
    int background_image; // �w�i�̉摜
    int hero_images[5]; // �E�҂̉摜�𕪊������z��
    int hero_standby[5];//�ҋ@�摜
    int hero_frame; // �E�҂̃A�j���[�V�����t���[��
    int hero_frame_count; // �t���[���X�V�p�J�E���^
    int hero_x; // �E�҂�X���W
    int hero_y; // �E�҂�Y���W
    int hero_direction; // �E�҂̌��� (1: �E����, -1: ������)

    bool is_moving; // �E�҂��ړ����Ă��邩�ǂ���
};
