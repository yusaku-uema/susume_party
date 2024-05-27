#include"DxLib.h"

#include"EnemyManager.h"

//ザコ敵
#include"Slime.h"
#include"Bird.h"
#include"Flower.h"
#include"Fairy.h"

//ボス
#include"BlackMage.h"


//#include"Stage.h"

#define DRAW_ARROW_TIME 2.0f//プレイヤーを指す矢印の表示時間

EnemyManager::EnemyManager(class Stage* stage, class PlayerManager* player_manager, class AttackManager* attack_manager)
{
    slime = new Slime(stage, player_manager, attack_manager);
    bird = new Bird(stage, player_manager, attack_manager);
    flower = new Flower(stage, player_manager, attack_manager);
    fairy = new Fairy(stage, player_manager, attack_manager);

    OutputDebugString("EnemyManagerコンストラクタ呼ばれました。\n");
}

EnemyManager::~EnemyManager()
{
    delete slime;
    delete bird;
    delete flower;

    OutputDebugString("EnemyManagerデストラクタが呼ばれました。\n");
}

void EnemyManager::Update(float delta_time)
{
    slime->Update(delta_time);
    flower->Update(delta_time);
    bird->Update(delta_time);
    fairy->Update(delta_time);
}

void EnemyManager::Draw() const
{
    slime->Draw();
    bird->Draw();
    flower->Draw();
    fairy->Draw();
}