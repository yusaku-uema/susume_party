#pragma once
#include"CharacterBase.h"
#include"PlayerManager.h"
#include"Stage.h"

enum class SLIME_STATE
{
    NORMAL,   //通常移動 
    ATTACK //攻撃
};

class Slime : public CharacterBase
{
private:
    
    int slime_image[12]; //スライムの画像
    int image_type; //使う画像の指定

    long int time;//時間測定

    bool move_left; //左に動くか

    SLIME_STATE state; //スライムの状態

public:
    Slime();
    ~Slime();

    void Update(float delta_time, class Stage* stage, class PlayerManager* player);
    void Draw(float camera_work) const;
    void Move(class Stage* stage, class PlayerManager* player); //通常移動
    void Attack(class Stage* stage, class PlayerManager* player, float delta_time); //攻撃

    float CalculateDistance(class PlayerManager* player); //とりあえず先頭プレイヤーの距離計算したい。、できれば4人まとめて


};