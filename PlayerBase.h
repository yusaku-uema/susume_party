#pragma once
#include"CombatCharacterBase.h"
#include"AttackManager.h"

#define JUMP_LOG 40//過去数回分のジャンプの記録

class PlayerBase : public CombatCharacterBase
{
protected:
    int player_image[3][5];
    int weapon_image;

private:

    PLAYER_JOB player_job;

    bool is_leader;//キャラが先頭か？
    bool is_casket_fall;//棺桶が空から降っている間
    bool is_party_member;//パーティーが切り離されているか？
    bool is_set_casket;//棺桶状態にするか？（死亡直後に使用）

    int weapon_angle;//武器のふり幅

    void UpdateLeader();
    void UpdateFollower(PlayerBase* previous_player);

    bool jump_log[JUMP_LOG];//過去数回分のジャンプの記録

    void SetJumpLog(bool is_jump);//ジャンプログを更新
    bool GetJumpLog()const;//一番古いジャンプログを渡す

    virtual void SpecialSkill() {};

public:
    PlayerBase(DATA location,int hp,int mp,int attack_power, PLAYER_JOB player_job);
    ~PlayerBase();

    bool Update(float delta_time, PlayerBase* previous_player);
    void Draw() const;

    bool HitDamege(BoxCollider* bc, int attack_power)override;//攻撃に当たった時の処理（HPを減らしたり...）

    PLAYER_JOB GetPlayerJob()const;

    bool GetIsLeader()const;//このキャラが先頭か？
    void SetIsPartyMember(bool is_party_member);//パーティー切り離し切り替え
    bool GetIsPartyMember()const;
};