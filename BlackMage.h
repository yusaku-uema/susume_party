#pragma once
#include"EnemyBase.h"
#include"PlayerManager.h"
#include"Stage.h"
#include"AttackManager.h"

enum class BLACKMAGE_STATE
{
    WAIT, //プレイヤーが視覚に入るまでは待機命令
    NORMAL,   //通常移動 
    ATTACK, //攻撃
    ATTACK_STANDBY, //攻撃待機
    STANDBY //待機
};

class BlackMage :
    public EnemyBase
{
    int blackmage_image[14]; //ボス（黒魔導士）の画像
    int roundtrips; //画面を往復した回数
    
    bool move_up; //上に移動
    bool lock_on; //プレイヤーに狙いを定める。


    int old_hp;

    BLACKMAGE_STATE state; //バードの状態
    DATA old_location; //前の座標
    DATA player_location; //攻撃時のプレイヤーの位置


public:

    BlackMage(class Stage* stage, class PlayerManager* player_manager, class AttackManager* attack_manager); //コンストラクタ
    ~BlackMage(); //デストラクタ

    void Update()override; //更新処理
    void Draw() const override; //描画関係
    void Move(); //通常移動
    void Standby(); //プレイヤーが視覚に入るまで待機状態にする
    void Wait(); //攻撃準備時間
    void Attack(); //攻撃
    void MoveAttack(); //移動時の攻撃

    float CalculateDistance(); //とりあえず先頭プレイヤーの距離計算したい。、できれば4人まとめて

};

