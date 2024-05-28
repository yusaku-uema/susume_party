#pragma once
#include"PlayerBase.h"


#define PLAYER_NUM 4//プレイヤー（キャラの数）

class PlayerManager
{
private:
    class PlayerBase* player[4];
    class Stage* stage;

    int arrow_image;//先頭プレイヤーを指す矢印画像
    float draw_arrow_time;//矢印の表示時間

    void DeadPlayerSorting(int dead_player);//死亡キャラの並び替え
    void PlayerSorting();//プレイヤー並び替え
public:

    PlayerManager(class Stage* stage, class AttackManager* attack_manager, class Ui* ui);
    ~PlayerManager();

    void CheckHitDamage(BoxCollider* bc, int attack_power);//攻撃が当たったか確かめる

    void Update(float delta_time);
    void Draw() const;

    DATA GetPlayerLocation()const;
    
};