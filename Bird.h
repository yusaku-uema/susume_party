#pragma once
#include"PlayerManager.h"
#include"EnemyManager.h"
#include"EnemyBase.h"
#include"Stage.h"



enum class BIRD_STATE
{
    NORMAL,   //通常移動 
    ATTACK, //攻撃
    STANDBY, //待機。
    RETURN //攻撃後、攻撃する前の座標に戻る
};



class Bird :
    public EnemyBase
{
private:

    int time;//攻撃待機時間
    int bird_image[11]; //バードの画像
    int image_type; //使う画像の要素指定
    long int animation_time; //画像切替に使う変数
  
   

    float distance_moved; //動いた距離
    float attack_speed; //攻撃速度
    float distance; //相手との距離
    float dx, dy; //変化量

    bool move_up; //上に移動
    bool move_left; //左に動く
    bool direction; //向いている方向
    bool lock_on; //プレイヤーに狙いを定める。


    BIRD_STATE state; //バードの状態
    DATA old_location; //前の座標
    DATA player_location; //攻撃時のプレイヤーの位置
    

public:

    Bird(class Stage* stage, class PlayerManager* player_manager, class AttackManager* attack_manager); //コンストラクタ
    ~Bird(); //デストラクタ

    void Update()override; //更新処理
    void Draw() const override; //描画関係
    void Move(); //通常移動
    void Standby(); //攻撃準備時間
    void Attack(); //攻撃
    void Retur(); //攻撃後元の座標に戻る。

    float CalculateDistance(); //とりあえず先頭プレイヤーの距離計算したい。、できれば4人まとめて

};

