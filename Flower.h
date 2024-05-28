#pragma once
#include"EnemyBase.h"
#include"PlayerManager.h"
#include"Stage.h"

enum class FLOWER_STATE
{
    ATTACK, //攻撃
    STANDBY //待機
};

class Flower :
    public EnemyBase
{
    int time; //アニメーション時間測定
    int flower_image[7]; //フラワーの画像
    int image_type; //使う画像の要素指定
    long int animation_time; //画像切替に使う変数


    bool start_attack; //攻撃開始
    bool direction; //向いている方向

    FLOWER_STATE state; //フラワーの状態


public:

    Flower(class Stage* stage, class PlayerManager* player_manager, class AttackManager* attack_manager);
    ~Flower();

    void Update(); //更新処理
    void Draw() const; //描画関係
    void Attack(); //攻撃

    float CalculateDistance(); //とりあえず先頭プレイヤーの距離計算したい。、できれば4人まとめて

};

