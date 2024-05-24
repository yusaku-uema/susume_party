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
    int time; //�A�j���[�V�������ԑ���
    int flower_image[7]; //�t�����[�̉摜
    int image_type; //�g���摜�̗v�f�w��
    long int animation_time; //�摜�ؑւɎg���ϐ�


    bool start_attack; //�U���J�n
    bool direction; //�����Ă������

    FLOWER_STATE state; //�t�����[�̏��


public:

    Flower(class Stage* stage, class PlayerManager* player_manager);
    ~Flower();

    void Update(float delta_time); //�X�V����
    void Draw() const; //�`��֌W
    void Attack(float delta_time); //�U��

    float CalculateDistance(); //�Ƃ肠�����擪�v���C���[�̋����v�Z�������B�A�ł����4�l�܂Ƃ߂�

};

