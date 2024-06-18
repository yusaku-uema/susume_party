#include "GameOverScene.h"
#include "DxLib.h"

GameOverScene::GameOverScene() : alpha(0), alpha_speed(2), message(nullptr), option_selected(false), message_displayed(false)
{
    // �Q�[���I�[�o�[�����摜
    if ((gameover_image = LoadGraph("image/GameOver/gameover.png")) == -1)
        throw("image/GameOver/gameover.png���ǂݍ��߂܂���\n");

    // ���b�Z�[�W�쐬
    message = new Message("txt/gameover.txt");

    // �I�����摜�̓ǂݍ���
    option_yes_image = LoadGraph("image/GameOver/yes.png");
    option_no_image = LoadGraph("image/GameOver/no.png");

    if (option_yes_image == -1 || option_no_image == -1)
        throw("yes.png��no.png���ǂݍ��܂�܂���ł���\n");
}

GameOverScene::~GameOverScene()
{
    // �摜�̍폜
    DeleteGraph(gameover_image);
    DeleteGraph(option_yes_image);
    DeleteGraph(option_no_image);
    delete message; // ���b�Z�[�W�̍폜
}

void GameOverScene::Initialize()
{
    alpha = 0; // ���������ɓ����x�����Z�b�g
    message_displayed = false; // ���b�Z�[�W�\���t���O�����Z�b�g
}

void GameOverScene::Finalize()
{
}

SCENE_TYPE GameOverScene::Update(float delta_time)
{
    // �����x�̑���
    if (alpha < 255)
    {
        alpha += alpha_speed; // �t�F�[�h�̑��x
        if (alpha > 255) alpha = 255; // �ő�l�𒴂��Ȃ��悤��
    }
    else
    {
        // ���b�Z�[�W�̍X�V
        if (!message_displayed && message->Update(delta_time))
        {
            // ���b�Z�[�W�����ׂĕ\�����ꂽ��̏���
            message_displayed = true; // ���b�Z�[�W�\���t���O��ݒ�
        }

        if (message_displayed) {
            // �\���L�[�̓��͏�Ԃ��擾
            int pad_input = GetJoypadInputState(DX_INPUT_PAD1);

            // ���X�e�B�b�N�̓���
            int l_stick_x, l_stick_y;
            GetJoypadAnalogInput(&l_stick_x, &l_stick_y, DX_INPUT_PAD1);

            // �X�e�B�b�N�̍����͏���
            if (l_stick_x < -8000 || (pad_input & PAD_INPUT_LEFT))
            {
                option_selected = true; // �u�͂��v��I��
            }
            // �X�e�B�b�N�̉E���͏���
            else if (l_stick_x > 8000 || (pad_input & PAD_INPUT_RIGHT))
            {
                option_selected = false; // �u�������v��I��
            }

            // �I������̏���
            if (pad_input & PAD_INPUT_B) // A�{�^���iXbox�R���g���[���[��A�{�^���j
            {
                if (option_selected)
                {
                    // �u�͂��v��I�������ꍇ�̏���
                    // ���̃V�[���֑J�ڂ��鏈���������ɒǉ�
                    return SCENE_TYPE::TITLE;
                   
                }
                else
                {
                    // �u�������v��I�������ꍇ�̏���
                    // �Q�[���I�[�o�[�ɖ߂鏈���������ɒǉ�
                    return SCENE_TYPE::MAIN;
                   
                }
            }
        }
    }
    return GetNowScene();
}

void GameOverScene::Draw() const
{
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha); // �A���t�@�u�����h���[�h�ɐݒ肵�ĕ`��
    DrawGraph(325, 50, gameover_image, TRUE); // �Q�[���I�[�o�[�����̕\��
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); // �u�����h���[�h�����ɖ߂�

    // ���b�Z�[�W�\��
    if (alpha == 255) {
        message->Draw();

        // ���b�Z�[�W���\������I�������Ɂu�������v�̉摜��\��
        if (message_displayed) {
          

            // �I�����̕\��
            if (option_selected)
            {
                //DrawString(0, 40, "�f�o�b�N: �͂�", 0xffffff);
                DrawGraph(200, 0, option_yes_image, TRUE);
            }
            else
            {
                //DrawString(0, 60, "�f�o�b�N: ������", 0xffffff);
                DrawGraph(200, 0, option_no_image, TRUE);
            }
        }
    }
    
}

SCENE_TYPE GameOverScene::GetNowScene() const
{
    return SCENE_TYPE::GAME_OVER;
}
