#pragma once
#include"EnemyBase.h"
#include"PlayerManager.h"
#include"Stage.h"
#include"AttackManager.h"

enum class BLACKMAGE_STATE
{
    WAIT, //�v���C���[�����o�ɓ���܂ł͑ҋ@����
    NORMAL,   //�ʏ�ړ� 
    ATTACK, //�U��
    ATTACK_STANDBY, //�U���ҋ@
    TELEPORT, //�e���|�[�g
    STANDBY //�ҋ@
};

class BlackMage :
    public EnemyBase
{
    int blackmage_image[14]; //�{�X�i�������m�j�̉摜
    int tentacle_image[10]; 
    int lock_image[10];
    int charge_image[10];
    int roundtrips; //��ʂ�����������
    int animation_type;
    int num; //
    
    bool move_up; //��Ɉړ�
    bool lock_on; //�v���C���[�ɑ_�����߂�B
    bool attack; //�U���J�n
    bool start_animation;


    int old_hp;

    BLACKMAGE_STATE state; //�o�[�h�̏��
    DATA old_location; //�O�̍��W
    DATA attack_location; //�U�����̃v���C���[�̈ʒu


public:

    BlackMage(class Stage* stage, class PlayerManager* player_manager, class AttackManager* attack_manager, DATA location); //�R���X�g���N�^
    ~BlackMage(); //�f�X�g���N�^

    void Update()override; //�X�V����
    void Draw() const override; //�`��֌W
    void Move(); //�ʏ�ړ�
    void Standby(); //�v���C���[�����o�ɓ���܂őҋ@��Ԃɂ���
    void Wait(); //�U����������
    void Attack(); //�U��
    void MoveAttack(); //�ړ����̍U��
    void TeleportAttack(); //�e���|�[�g���čU������

    float CalculateDistance(); //�Ƃ肠�����擪�v���C���[�̋����v�Z�������B�A�ł����4�l�܂Ƃ߂�

};

