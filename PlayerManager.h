#pragma once
#include"PlayerBase.h"


#define PLAYER_NUM 4//プレイヤー（キャラの数）

class PlayerManager
{
private:
    class PlayerBase* player[4];
    class Stage* stage;
    int dead_player_count;
    int arrow_image;//先頭プレイヤーを指す矢印画像
    float draw_arrow_time;//矢印の表示時間

    void DeadPlayerSorting(int dead_player_index);//死亡キャラの並び替え
    void PlayerSorting();//プレイヤー並び替え

public:

    PlayerManager(class Stage* stage, class AttackManager* attack_manager, class Ui* ui);
    ~PlayerManager();

    bool CheckHitDamage(class BoxCollider* bc, int attack_power);//攻撃が当たったか確かめる

    void Update(float delta_time);//戻り値（プレイヤーが全滅したら　TRUEを返す）
    void Draw() const;

    DATA GetPlayerLocation()const;
    
};