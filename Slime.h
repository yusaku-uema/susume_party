#pragma once
#include"EnemyBase.h"
#include"PlayerManager.h"
#include"Stage.h"

enum class SLIME_STATE
{
    NORMAL,   //通常移動 
    STANDBY, //待機。
    ATTACK, //攻撃
    DEATH //死亡
};

class Slime : public EnemyBase
{
private:
    
    int slime_image[12]; //スライムの画像
    int image_type; //使う画像の指定

    long int time;//時間測定

    bool move_left; //左に動くか

    SLIME_STATE state; //スライムの状態

public:
    Slime(class Stage* stage, class PlayerManager* player_manager, class AttackManager* attack_manager, DATA location);
    ~Slime();

    void Update()override;
    void Draw() const override;
    void Move(); //通常移動
    void Attack(); //攻撃
    void Standby(); //待機

    float CalculateDistance(); //とりあえず先頭プレイヤーの距離計算したい。、できれば4人まとめて


};