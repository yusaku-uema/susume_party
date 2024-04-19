#pragma once
#include"CharacterBase.h"
#include"Stage.h"

#define JUMP_LOG 30//過去数回分のジャンプの記録

class PlayerBase : public CharacterBase
{
private:
    bool is_dead;//死んでいるか？

    void MoveX(class Stage* stage, PlayerBase* player);//X座標の更新
    void MoveY(class Stage* stage, PlayerBase* previous_player);//Y座標の更新
    bool jump_log[JUMP_LOG];//過去数回分のジャンプの記録
    void SetJumpLog(bool is_jump);//ジャンプログを更新
    bool GetJumpLog()const;//一番古いジャンプログを渡す
public:

    PlayerBase();
    ~PlayerBase();

    void Update(float delta_time, class Stage* stage, PlayerBase* previous_player);
    void Draw() const;
};