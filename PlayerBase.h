#pragma once
#include"CharacterBase.h"

#define JUMP_LOG 40//過去数回分のジャンプの記録

class PlayerBase : public CharacterBase
{
protected:
    int player_image[3][5];

private:

    PLAYER_JOB player_job;
    
    bool is_dead;//死んでいるか？
    bool is_facing_left;//左を向いているか？
    bool is_leader;//キャラが先頭か？
    bool is_casket_fall;//棺桶が空から降っている間
    bool is_party_member;//パーティーが切り離されているか？
    bool is_set_casket;//棺桶状態にするか？（死亡直後に使用）

    float image_change_time;//画像切り替え時間
    int draw_image_num;//表示画像の番号

    void UpdateLeader();
    void UpdateFollower(PlayerBase* previous_player);

    bool jump_log[JUMP_LOG];//過去数回分のジャンプの記録

    void SetJumpLog(bool is_jump);//ジャンプログを更新
    bool GetJumpLog()const;//一番古いジャンプログを渡す

public:

    PlayerBase(PLAYER_JOB player_job);
    ~PlayerBase();

    bool Update(float delta_time, PlayerBase* previous_player);
    void Draw() const;

    bool HitDamege(int attack_power)override;//攻撃に当たった時の処理（HPを減らしたり...）

    bool GetIsDead()const;//プレイヤーが死んでいるか？

    PLAYER_JOB GetPlayerJob()const;

    bool GetIsLeader()const;//このキャラが先頭か？
};