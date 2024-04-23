#pragma once

#define SCREEN_WIDTH 1280 //����ʃT�C�Y
#define SCREEN_HEIGHT 720 //�c��ʃT�C�Y

#define STAGE_BLOCK_NUM_Y 10 //�X�e�[�W�̏c�u���b�N�̐�
#define STAGE_BLOCK_NUM_X 60 //�X�e�[�W�̉��u���b�N�̐�

#define BLOCK_SIZE 50.0f //�u���b�N�̃T�C�Y

#define GRAVITY 0.4f //�d�͂̑傫��
#define FALL_SPEED 5.0f//�������x�̍ő�l

struct DATA //���W,�傫��,�X�s�[�h�ȂǂɎg��
{
    float x, y;
};

enum class BLOCK_TYPE
{
    GRASSLAND_BLOCK = 1,//�����u���b�N
    SOIL_BLOCK,//�y�u���b�N
};