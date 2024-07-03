#pragma once
#include"EnemyBase.h"

class Bird : public EnemyBase
{
private:

    DATA target_location;//攻撃する座標
    DATA begin_attack_location;//攻撃開始座標
    float attack_speed; //攻撃速度

public:

    Bird(DATA location, int enemy_image[ENEMY_STATE::END][5], class Stage* stage, class PlayerManager* player_manager, class AttackManager* attack_manager); //コンストラクタ
    ~Bird(); //デストラクタ

    void Update(float delta_time)override; //更新処理
    void Draw(DATA draw_location) const override; //描画関係
};

