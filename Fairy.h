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
    int bird_image[12]; //�d���̉摜
    int image_type; //�g���摜�̗v�f�w��
    long int animation_time; //�摜�ؑւɎg���ϐ�


    float distance_moved; //����������
    float attack_speed; //�U�����x
    float distance; //����Ƃ̋���
    float dx, dy; //�ω���

    bool start_attack; //�U���J�n
    bool standby_attack; //�U������ (�󒆑ҋ@)
    bool move_left; //���ɓ���
    bool direction; //�����Ă������
    bool lock_on; //�v���C���[�ɑ_�����߂�B


    FAIRY_STATE state; //�d���̏��
    DATA old_location; //�O�̍��W
    DATA player_location; //�U�����̃v���C���[�̈ʒu


public:

    Fairy(); //�R���X�g���N�^
    ~Fairy(); //�f�X�g���N�^

    void Update(float delta_time, class Stage* stage, class PlayerManager* player); //�X�V����
    void Draw(float camera_work) const; //�`��֌W
    void Move(class Stage* stage, class PlayerManager* player); //�ʏ�ړ�
    void Standby(class PlayerManager* player); //�U����������
    void Attack(class Stage* stage, class PlayerManager* player, float delta_time); //�U��

    float CalculateDistance(class PlayerManager* player); //�Ƃ肠�����擪�v���C���[�̋����v�Z�������B�A�ł����4�l�܂Ƃ߂�

};

