//#pragma once
//#include "EnemyBase.h"
//#include"PlayerManager.h"
//#include"Stage.h"
//
//enum class FAIRY_STATE
//{
//    NORMAL,   //通常移動 
//    ATTACK, //攻撃
//    STANDBY, //待機。
//    DEATH //死亡
//};
//
//
//class Fairy :
//    public EnemyBase
//{
//private:
//    
//    int time;//攻撃待機時間
//    int fairy_image[12]; //妖精の画像
//    int image_type; //使う画像の要素指定
//    long int animation_time; //画像切替に使う変数
//
//
//    float distance_moved; //動いた距離
//    float attack_speed; //攻撃速度
//    float distance; //相手との距離
//    float dx, dy; //変化量
//
//    bool move_left; //左に動く
//    bool direction; //向いている方向
//    bool lock_on; //プレイヤーに狙いを定める。
//
//
//    FAIRY_STATE state; //妖精の状態
//    DATA player_location; //攻撃時のプレイヤーの位置
//
//
//public:
//
//    Fairy(class Stage* stage, class PlayerManager* player_manager, class AttackManager* attack_manager, DATA location); //コンストラクタ
//    ~Fairy(); //デストラクタ
//
//    void Update()override; //更新処理
//    void Draw() const override; //描画関係
//    void Move(); //通常移動
//    void Standby(); //攻撃準備時間
//    void Attack(); //攻撃
//
//    float CalculateDistance(); //とりあえず先頭プレイヤーの距離計算したい。、できれば4人まとめて
//
//};
//
