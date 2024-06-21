#pragma once

#include "SceneBase.h"
#include "Message.h"

class GameClearScene : public SceneBase {
private:
    Message* message; // ���b�Z�[�W�\���p�̃C���X�^���X
    int clear_image; // �N���A�̃��S�摜
    int king_image; // ���l�̉摜
    int background_image; // �w�i�̉摜
    int hero_images[5]; // �E�҂̉摜�𕪊������z��
    int hero_standby[5]; // �ҋ@�摜
    int hero_frame; // �E�҂̃A�j���[�V�����t���[��
    int hero_frame_count; // �t���[���X�V�p�J�E���^
    int hero_x; // �E�҂�X���W
    int hero_y; // �E�҂�Y���W
    int hero_direction; // �E�҂̌��� (1: �E����, -1: ������)
    int bgm;

    bool is_moving; // �E�҂��ړ����Ă��邩�ǂ���
  
public:
    GameClearScene();
    ~GameClearScene();
    void Initialize();
    void Finalize();
    SCENE_TYPE Update(float delta_time);
    void Draw() const;
    SCENE_TYPE GetNowScene() const;
};