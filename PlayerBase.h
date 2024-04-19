#pragma once
#include"CharacterBase.h"
#include"Stage.h"

#define JUMP_LOG 30//�ߋ����񕪂̃W�����v�̋L�^

class PlayerBase : public CharacterBase
{
private:
    bool is_dead;//����ł��邩�H

    void MoveX(class Stage* stage, PlayerBase* player);//X���W�̍X�V
    void MoveY(class Stage* stage, PlayerBase* previous_player);//Y���W�̍X�V
    bool jump_log[JUMP_LOG];//�ߋ����񕪂̃W�����v�̋L�^
    void SetJumpLog(bool is_jump);//�W�����v���O���X�V
    bool GetJumpLog()const;//��ԌÂ��W�����v���O��n��
public:

    PlayerBase();
    ~PlayerBase();

    void Update(float delta_time, class Stage* stage, PlayerBase* previous_player);
    void Draw() const;
};