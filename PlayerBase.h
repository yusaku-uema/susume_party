#pragma once
#include"CharacterBase.h"
#include"Stage.h"
#include"PlayerManager.h"

#define JUMP_LOG 30//過去数回分のジャンプの記録

class PlayerBase : public CharacterBase
{
protected:
    int player_image[4];
private:
    int color;//プレイヤーの色
    bool is_dead;//死んでいるか？

    void MoveX(class Stage* stage, PlayerBase* player);//X座標の更新
    void MoveY(class Stage* stage, PlayerBase* previous_player);//Y座標の更新
    bool jump_log[JUMP_LOG];//過去数回分のジャンプの記録
    void SetJumpLog(bool is_jump);//ジャンプログを更新
    bool GetJumpLog()const;//一番古いジャンプログを渡す

    void Attack(class PlayerManager* player_manager);

public:

    PlayerBase(int color);
    ~PlayerBase();

    void Update(float delta_time, class Stage* stage, PlayerBase* previous_player, PlayerManager* player_manager);
    void Draw(float camera_work) const;

    bool GetIsDead()const;//プレイヤーが死んでいるか？
};