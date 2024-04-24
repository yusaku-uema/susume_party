#pragma once
#include "CharacterBase.h"
#include"PlayerManager.h"
#include"Stage.h"

class Bird :
    public CharacterBase
{
private:

    float distance_moved; //動いた距離

    bool start_attack; //攻撃開始
    bool move_up; //上に移動
    bool move_left; //左に動く

public:

    Bird(); //コンストラクタ
    ~Bird(); //デストラクタ

    void Update(float delta_time, class Stage* stage, class PlayerManager* player); //更新処理
    void Draw(float camera_work) const; //描画関係

    float CalculateDistance(class PlayerManager* player); //とりあえず先頭プレイヤーの距離計算したい。、できれば4人まとめて

};

