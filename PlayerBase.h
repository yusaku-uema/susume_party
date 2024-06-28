#pragma once
#include"CombatCharacterBase.h"
#include"AttackManager.h"

#define JUMP_LOG 40//�ߋ����񕪂̃W�����v�̋L�^

class PlayerBase : public CombatCharacterBase
{
protected:
    int player_image[3][5];
    int weapon_image;

private:

    PLAYER_JOB player_job;

    bool is_leader;//�L�������擪���H
    bool is_casket_fall;//�������󂩂�~���Ă����
    bool is_party_member;//�p�[�e�B�[���؂藣����Ă��邩�H
    bool is_set_casket;//������Ԃɂ��邩�H�i���S����Ɏg�p�j

    int weapon_angle;//����̂ӂ蕝

    void UpdateLeader();
    void UpdateFollower(PlayerBase* previous_player);

    bool jump_log[JUMP_LOG];//�ߋ����񕪂̃W�����v�̋L�^

    void SetJumpLog(bool is_jump);//�W�����v���O���X�V
    bool GetJumpLog()const;//��ԌÂ��W�����v���O��n��

    virtual void SpecialSkill() {};

public:
    PlayerBase(DATA location,int hp,int mp,int attack_power, PLAYER_JOB player_job);
    ~PlayerBase();

    bool Update(float delta_time, PlayerBase* previous_player);
    void Draw() const;

    bool HitDamege(BoxCollider* bc, int attack_power)override;//�U���ɓ����������̏����iHP�����炵����...�j

    PLAYER_JOB GetPlayerJob()const;

    bool GetIsLeader()const;//���̃L�������擪���H
    void SetIsPartyMember(bool is_party_member);//�p�[�e�B�[�؂藣���؂�ւ�
    bool GetIsPartyMember()const;
};