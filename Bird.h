#pragma once
#include "CharacterBase.h"
#include"PlayerManager.h"
#include"Stage.h"



enum class BIRD_STATE
{
    NORMAL,   //�ʏ�ړ� 
    ATTACK, //�U��
    STANDBY //�ҋ@�B
};



class Bird :
    public CharacterBase
{
private:

    int time;//�U���ҋ@����

    float distance_moved; //����������

    bool start_attack; //�U���J�n
    bool standby_attack; //�U������ (�󒆑ҋ@)
    bool move_up; //��Ɉړ�
    bool move_left; //���ɓ���


    BIRD_STATE state; //�o�[�h�̏��


public:

    Bird(); //�R���X�g���N�^
    ~Bird(); //�f�X�g���N�^

    void Update(float delta_time, class Stage* stage, class PlayerManager* player); //�X�V����
    void Draw(float camera_work) const; //�`��֌W
    void Move(class Stage* stage, class PlayerManager* player); //�ʏ�ړ�
    void Standby(class PlayerManager* player); //�U����������


    float CalculateDistance(class PlayerManager* player); //�Ƃ肠�����擪�v���C���[�̋����v�Z�������B�A�ł����4�l�܂Ƃ߂�

};

