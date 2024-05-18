#pragma once
#include"CharacterBase.h"
#include"Stage.h"

#define JUMP_LOG 40//過去数回分のジャンプの記録

class PlayerBase : public CharacterBase
{
protected:
    int player_image[2][5];

private:
    class Stage* stage;

    PLAYER_JOB player_job;
    
    bool is_dead;//死んでいるか？
    bool is_facing_left;//左を向いているか？
    bool is_leader;//キャラが先頭か？
    float image_change_time;//画像切り替え時間
    int draw_image_num;//表示画像の番号

    void UpdateLeader();
    void UpdateFollower(PlayerBase* previous_player);

    bool jump_log[JUMP_LOG];//過去数回分のジャンプの記録
    void SetJumpLog(bool is_jump);//ジャンプログを更新
    bool GetJumpLog()const;//一番古いジャンプログを渡す

public:

    PlayerBase(class Stage* stage,PLAYER_JOB player_job);
    ~PlayerBase();

    void Update(float delta_time, PlayerBase* previous_player);
    void Draw(float camera_work) const;

    bool GetIsDead()const;//プレイヤーが死んでいるか？
    PLAYER_JOB GetPlayerJob()const;
    bool GetIsLeader()const;//このキャラが先頭か？
};