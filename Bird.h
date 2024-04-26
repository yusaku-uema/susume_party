#pragma once
#include "CharacterBase.h"
#include"PlayerManager.h"
#include"Stage.h"



enum class BIRD_STATE
{
    NORMAL,   //通常移動 
    ATTACK, //攻撃
    STANDBY, //待機。
    RETURN //攻撃後、攻撃する前の座標に戻る
};



class Bird :
    public CharacterBase
{
private:

    int time;//攻撃待機時間

    float distance_moved; //動いた距離
    float attack_speed; //攻撃速度
    float distance; //相手との距離
    float dx, dy; //変化量

    bool start_attack; //攻撃開始
    bool standby_attack; //攻撃準備 (空中待機)
    bool move_up; //上に移動
    bool move_left; //左に動く


    BIRD_STATE state; //バードの状態
    DATA old_location; //前の座標
    

public:

    Bird(); //コンストラクタ
    ~Bird(); //デストラクタ

    void Update(float delta_time, class Stage* stage, class PlayerManager* player); //更新処理
    void Draw(float camera_work) const; //描画関係
    void Move(class Stage* stage, class PlayerManager* player); //通常移動
    void Standby(class PlayerManager* player); //攻撃準備時間
    void Attack(class Stage* stage, class PlayerManager* player, float delta_time); //攻撃
    void Retur(); //攻撃後元の座標に戻る。

    float CalculateDistance(class PlayerManager* player); //とりあえず先頭プレイヤーの距離計算したい。、できれば4人まとめて

};

