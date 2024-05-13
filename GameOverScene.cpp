#include "GameOverScene.h"
#include "Key.h"
#include "DxLib.h"
#include <fstream>


GameOverScene::GameOverScene() {
    // �Q�[���I�[�o�[�摜�̓ǂݍ���
    if ((gameover_image = LoadGraph("image/GameOver/gameover.png")) == -1)
        throw("�Q�[���I�[�o�[�摜�Ǎ��ݎ��s\n");

    transparency = 0;
    transparencySpeed = 1;
    imagePosX = 350;
    imagePosY = 0;

}


GameOverScene::~GameOverScene() {}

// ����������
void GameOverScene::Initialize() {}

// �I��������
void GameOverScene::Finalize() {}

// �X�V����
SCENE_TYPE GameOverScene::Update(float delta_time) {
    if (transparency < 255) {
        transparency += transparencySpeed;
    }
    if (transparency == 255 && textIndex < textLength) {
        textIndex++;  // �e�L�X�g���ꕶ�������₷
    }

    return GetNowScene();
}

// �`�揈��
void GameOverScene::Draw() const {
    // �����x�ݒ�
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, transparency);

    // �摜�`��
    DrawGraph(imagePosX, imagePosY, gameover_image, TRUE);


    // �����x�����ɖ߂�
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

// ���݂̃V�[�������擾
SCENE_TYPE GameOverScene::GetNowScene() const {
    return SCENE_TYPE::GAME_OVER;
}
