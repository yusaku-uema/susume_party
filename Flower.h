#pragma once
#include"EnemyBase.h"
#include"PlayerManager.h"
#include"Stage.h"

enum class FLOWER_STATE
{
    ATTACK, //攻撃
    STANDBY, //待機
    BREAKTIME, //攻撃後の待機時間
    DEATH //エネミー死亡
};

class Flower :
    public EnemyBase
{
    int time; //アニメーション時間測定
    int flower_image[7]; //フラワーの画像
    int image_type; //使う画像の要素指定
    int standby_time; //攻撃後の待機時間測定
    long int animation_time; //画像切替に使う変数


    bool start_attack; //攻撃開始
    bool direction; //向いている方向

    FLOWER_STATE state; //フラワーの状態


public:

    Flower(class Stage* stage, class PlayerManager* player_manager, class AttackManager* attack_manager, DATA location);
    ~Flower();

    void Update()override; //更新処理
    void Draw() const override; //描画関係
    void Attack(); //攻撃

    float CalculateDistance(); //とりあえず先頭プレイヤーの距離計算したい。、できれば4人まとめて

};

