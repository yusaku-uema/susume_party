#pragma once
#include"PlayerBase.h"
#include"Stage.h"

#define PLAYER_NUM 4//プレイヤー（キャラの数）

class PlayerManager
{
private:
    class PlayerBase* player[4];

    int arrow_image;//先頭プレイヤーを指す矢印画像
    float draw_arrow_time;//矢印の表示時間

    int alive_player;//生きてるプレイヤー数

    void DeadPlayerSorting();//死亡キャラの並び替え
    void PlayerSorting();//プレイヤー並び替え
public:

    PlayerManager(class Stage* stage, class Ui* ui);
    ~PlayerManager();

    void Update(float delta_time);
    void Draw(float camera_work) const;

    DATA GetPlayerLocation()const;
    
};