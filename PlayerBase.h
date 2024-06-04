#pragma once
#include"CharacterBase.h"

#define JUMP_LOG 40//�ߋ����񕪂̃W�����v�̋L�^

class PlayerBase : public CharacterBase
{
protected:
    int player_image[3][5];

private:

    PLAYER_JOB player_job;
    
    bool is_dead;//����ł��邩�H
    bool is_facing_left;//���������Ă��邩�H
    bool is_leader;//�L�������擪���H
    bool is_casket_fall;//�������󂩂�~���Ă����
    bool is_party_member;//�p�[�e�B�[���؂藣����Ă��邩�H
    bool is_set_casket;//������Ԃɂ��邩�H�i���S����Ɏg�p�j

    float image_change_time;//�摜�؂�ւ�����
    int draw_image_num;//�\���摜�̔ԍ�

    void UpdateLeader();
    void UpdateFollower(PlayerBase* previous_player);

    bool jump_log[JUMP_LOG];//�ߋ����񕪂̃W�����v�̋L�^

    void SetJumpLog(bool is_jump);//�W�����v���O���X�V
    bool GetJumpLog()const;//��ԌÂ��W�����v���O��n��

public:

    PlayerBase(PLAYER_JOB player_job);
    ~PlayerBase();

    bool Update(float delta_time, PlayerBase* previous_player);
    void Draw() const;

    bool HitDamege(int attack_power)override;//�U���ɓ����������̏����iHP�����炵����...�j

    bool GetIsDead()const;//�v���C���[������ł��邩�H

    PLAYER_JOB GetPlayerJob()const;

    bool GetIsLeader()const;//���̃L�������擪���H
};