#pragma once
#include "CharacterBase.h"
#include"Stage.h"

class Bird :
    public CharacterBase
{
private:

    float distance_moved; //動いた距離

    bool move_up; //上に移動
    bool move_left; //左に動く
    bool fly; //飛ぶ

public:

    Bird(); //コンストラクタ
    ~Bird(); //デストラクタ

    void Update(float delta_time, class Stage* stage); //更新処理
    void Draw(float camera_work) const; //描画関係
};

