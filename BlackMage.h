#pragma once
#include "CharacterBase.h"

enum class BLACKMAGE_STATE
{
    NORMAL,   //�ʏ�ړ� 
    ATTACK, //�U��
    ATTACK_STANDBY, //�U���ҋ@
    STANDBY //�ҋ@
};

class BlackMage :
    public CharacterBase
{
    int time;//�U���ҋ@����
    int blackmage_image[11]; //�{�X�i�������m�j�̉摜
    int image_type; //�g���摜�̗v�f�w��
    long int animation_time; //�摜�ؑւɎg���ϐ�


    float distance_moved; //����������
    float attack_speed; //�U�����x
    float distance; //����Ƃ̋���
    float dx, dy; //�ω���

    bool move_up; //��Ɉړ�
    bool move_left; //���ɓ���
    bool direction; //�����Ă������
    bool lock_on; //�v���C���[�ɑ_�����߂�B


    BLACKMAGE_STATE state; //�o�[�h�̏��
    DATA old_location; //�O�̍��W
    DATA player_location; //�U�����̃v���C���[�̈ʒu


public:

    BlackMage(); //�R���X�g���N�^
    ~BlackMage(); //�f�X�g���N�^

    void Update(float delta_time, class Stage* stage, class PlayerManager* player); //�X�V����
    void Draw(float camera_work) const; //�`��֌W
    void Move(class Stage* stage, class PlayerManager* player); //�ʏ�ړ�
    void Standby(class PlayerManager* player); //�U����������
    void Attack(class Stage* stage, class PlayerManager* player, float delta_time); //�U��

    float CalculateDistance(class PlayerManager* player); //�Ƃ肠�����擪�v���C���[�̋����v�Z�������B�A�ł����4�l�܂Ƃ߂�

};

