#pragma once
#include "CharacterBase.h"
#include"PlayerManager.h"
#include"Stage.h"

enum class FLOWER_STATE
{
    ATTACK, //�U��
    STANDBY //�ҋ@
};

class Flower :
    public CharacterBase
{
    int time;//�U���ҋ@����
    int flower_image[7]; //�t�����[�̉摜
    int image_type; //�g���摜�̗v�f�w��
    long int animation_time; //�摜�ؑւɎg���ϐ�


    bool start_attack; //�U���J�n

    FLOWER_STATE state; //�t�����[�̏��


public:

    Flower();
    ~Flower();

    void Update(float delta_time, class Stage* stage, class PlayerManager* player); //�X�V����
    void Draw(float camera_work) const; //�`��֌W
    void Attack(class Stage* stage, class PlayerManager* player, float delta_time); //�U��

    float CalculateDistance(class PlayerManager* player); //�Ƃ肠�����擪�v���C���[�̋����v�Z�������B�A�ł����4�l�܂Ƃ߂�

};

