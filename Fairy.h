#pragma once
#include "CharacterBase.h"
#include"PlayerManager.h"
#include"Stage.h"

enum class FAIRY_STATE
{
    NORMAL,   //�ʏ�ړ� 
    ATTACK, //�U��
    STANDBY //�ҋ@�B
};


class Fairy :
    public CharacterBase
{
private:
    
    int time;//�U���ҋ@����
    int fairy_image[12]; //�d���̉摜
    int image_type; //�g���摜�̗v�f�w��
    long int animation_time; //�摜�ؑւɎg���ϐ�


    float distance_moved; //����������
    float attack_speed; //�U�����x
    float distance; //����Ƃ̋���
    float dx, dy; //�ω���

    bool move_left; //���ɓ���
    bool direction; //�����Ă������
    bool lock_on; //�v���C���[�ɑ_�����߂�B


    FAIRY_STATE state; //�d���̏��
    DATA player_location; //�U�����̃v���C���[�̈ʒu


public:

    Fairy(class Stage* stage, class PlayerManager* player_manager, class AttackManager* attack_manager); //�R���X�g���N�^
    ~Fairy(); //�f�X�g���N�^

    void Update(float delta_time); //�X�V����
    void Draw() const; //�`��֌W
    void Move(); //�ʏ�ړ�
    void Standby(); //�U����������
    void Attack(float delta_time); //�U��

    float CalculateDistance(); //�Ƃ肠�����擪�v���C���[�̋����v�Z�������B�A�ł����4�l�܂Ƃ߂�

};

