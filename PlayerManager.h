#pragma once
#include"PlayerBase.h"
#include"Message.h"

#define PLAYER_NUM 4//プレイヤー（キャラの数）

class PlayerManager
{
private:
    class Stage* stage;
    class EnemyManager* enemy_manager;
    class AttackManager* attack_manager;
    class Message* message;
    class Ui* ui;

    class PlayerBase* player[4];
    
    int arrow_image;//先頭プレイヤーを指す矢印画像
    float draw_arrow_time;//矢印の表示時間

    void DeadPlayerSorting(int dead_player_index);//死亡キャラの並び替え
    void PlayerSorting();//プレイヤー並び替え

public:

    PlayerManager();
    ~PlayerManager();

    void Initialize(class Stage* stage, class EnemyManager* enemy_manager, class AttackManager* attack_manager);

    bool CheckHitDamage(class BoxCollider* bc, int attack_power);//攻撃が当たったか確かめる

    bool Update(float delta_time);//戻り値（プレイヤーが全滅したら　TRUEを返す）
    void Draw() const;

    PlayerBase* GetPlayerData()const;

    void SetMessage(const char* text_data_name);//メッセージをセット
    bool GetiIsTalking()const;//会話中か確かめる関数
    void SetPartyState(bool party_state);//パーティーを切り離すかどうか
    void AddPlayerHp(int add_hp);//パーティー全体にHP加算
};