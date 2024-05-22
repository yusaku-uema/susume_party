#pragma once
#include "CharacterBase.h"

enum class BLACKMAGE_STATE
{
    NORMAL,   //通常移動 
    ATTACK, //攻撃
    ATTACK_STANDBY, //攻撃待機
    STANDBY //待機
};

class BlackMage :
    public CharacterBase
{
    int time;//攻撃待機時間
    int blackmage_image[11]; //ボス（黒魔導士）の画像
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


    BLACKMAGE_STATE state; //バードの状態
    DATA old_location; //前の座標
    DATA player_location; //攻撃時のプレイヤーの位置


public:

    BlackMage(); //コンストラクタ
    ~BlackMage(); //デストラクタ

    void Update(float delta_time, class Stage* stage, class PlayerManager* player); //更新処理
    void Draw(float camera_work) const; //描画関係
    void Move(class Stage* stage, class PlayerManager* player); //通常移動
    void Standby(class PlayerManager* player); //攻撃準備時間
    void Attack(class Stage* stage, class PlayerManager* player, float delta_time); //攻撃

    float CalculateDistance(class PlayerManager* player); //とりあえず先頭プレイヤーの距離計算したい。、できれば4人まとめて

};

