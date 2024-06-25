#pragma once

#define FONT_SIZE 35 // �����̑傫��

#define SCREEN_SIZE_X 1280 //����ʃT�C�Y
#define SCREEN_SIZE_Y 720 //�c��ʃT�C�Y

#define HALF_SCREEN_SIZE_X 640
#define HALF_SCREEN_SIZE_Y 360

#define STAGE_BLOCK_NUM_Y 15 //�X�e�[�W�̏c�u���b�N�̐�
#define STAGE_BLOCK_NUM_X 276 //�X�e�[�W�̉��u���b�N�̐�

#define BLOCK_TYPE_NUM 17//�u���b�N�̎��

#define BLOCK_SIZE 36.0f //�u���b�N�̃T�C�Y

#define GRAVITY 0.2f //�d�͂̑傫��
#define FALL_SPEED 5.0f//�������x�̍ő�l

#define ENEMY_EXPLOSION_SIZE 5

struct DATA //���W,�傫��,�X�s�[�h�ȂǂɎg��
{
    float x, y;
};

enum class PLAYER_JOB//�v���C���[�E��
{
    HERO,//�E��
    WARRIOR,//��m
    WIZARD,//���@�g��
    MONK//�m��
};