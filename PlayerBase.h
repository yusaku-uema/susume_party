#pragma once
#include"CharacterBase.h"
#include"Stage.h"
#include"PlayerManager.h"

#define JUMP_LOG 30//�ߋ����񕪂̃W�����v�̋L�^

class PlayerBase : public CharacterBase
{
protected:
    int player_image[4];
private:
    int color;//�v���C���[�̐F
    bool is_dead;//����ł��邩�H

    void MoveX(class Stage* stage, PlayerBase* player);//X���W�̍X�V
    void MoveY(class Stage* stage, PlayerBase* previous_player);//Y���W�̍X�V
    bool jump_log[JUMP_LOG];//�ߋ����񕪂̃W�����v�̋L�^
    void SetJumpLog(bool is_jump);//�W�����v���O���X�V
    bool GetJumpLog()const;//��ԌÂ��W�����v���O��n��

    void Attack(class PlayerManager* player_manager);

public:

    PlayerBase(int color);
    ~PlayerBase();

    void Update(float delta_time, class Stage* stage, PlayerBase* previous_player, PlayerManager* player_manager);
    void Draw(float camera_work) const;

    bool GetIsDead()const;//�v���C���[������ł��邩�H
};