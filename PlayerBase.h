#pragma once
#include"CharacterBase.h"
#include"Stage.h"

#define JUMP_LOG 40//�ߋ����񕪂̃W�����v�̋L�^

class PlayerBase : public CharacterBase
{
protected:
    int player_image[2][5];

private:
    class Stage* stage;

    PLAYER_JOB player_job;
    
    bool is_dead;//����ł��邩�H
    bool is_facing_left;//���������Ă��邩�H
    bool is_leader;//�L�������擪���H
    float image_change_time;//�摜�؂�ւ�����
    int draw_image_num;//�\���摜�̔ԍ�

    void UpdateLeader();
    void UpdateFollower(PlayerBase* previous_player);

    bool jump_log[JUMP_LOG];//�ߋ����񕪂̃W�����v�̋L�^
    void SetJumpLog(bool is_jump);//�W�����v���O���X�V
    bool GetJumpLog()const;//��ԌÂ��W�����v���O��n��

public:

    PlayerBase(class Stage* stage,PLAYER_JOB player_job);
    ~PlayerBase();

    void Update(float delta_time, PlayerBase* previous_player);
    void Draw(float camera_work) const;

    bool GetIsDead()const;//�v���C���[������ł��邩�H
    PLAYER_JOB GetPlayerJob()const;
    bool GetIsLeader()const;//���̃L�������擪���H
};