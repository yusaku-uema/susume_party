#pragma once
#include"PlayerBase.h"
#include"Stage.h"

#define PLAYER_NUM 4//プレイヤー（キャラの数）

class PlayerManager
{
private:
    class PlayerBase* player[4];
    void PlayerSorting();//プレイヤー並び替え
public:

    PlayerManager();
    ~PlayerManager();

    void Update(float delta_time, class Stage* stage);
    void Draw(float camera_work) const;

    DATA GetPlayerLocation()const;
};