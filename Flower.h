#pragma once
#include "CharacterBase.h"
#include"PlayerManager.h"
#include"Stage.h"

enum class FLOWER_STATE
{
    ATTACK, //攻撃
    STANDBY //待機
};

class Flower :
    public CharacterBase
{
    int time;//攻撃待機時間
    int flower_image[7]; //フラワーの画像
    int image_type; //使う画像の要素指定
    long int animation_time; //画像切替に使う変数


    bool start_attack; //攻撃開始

    FLOWER_STATE state; //フラワーの状態


public:

    Flower();
    ~Flower();

    void Update(float delta_time, class Stage* stage, class PlayerManager* player); //更新処理
    void Draw(float camera_work) const; //描画関係
    void Attack(class Stage* stage, class PlayerManager* player, float delta_time); //攻撃

    float CalculateDistance(class PlayerManager* player); //とりあえず先頭プレイヤーの距離計算したい。、できれば4人まとめて

};

