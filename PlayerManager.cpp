#include"DxLib.h"
#include"PlayerManager.h"
#include"Key.h"
#include"Stage.h"
#include"Ui.h"
#include"Hero.h"
#include"Warrior.h"
#include"Wizard.h"
#include"Monk.h"

#define DRAW_ARROW_TIME 2.0f//プレイヤーを指す矢印の表示時間

PlayerManager::PlayerManager(class Stage* stage, class AttackManager* attack_manager, class Ui* ui) : stage(stage), draw_arrow_time(0.0f)
{
    player[0] = new Hero(stage, this, attack_manager);//勇者
    player[1] = new Warrior(stage, this, attack_manager);//戦士
    player[2] = new Wizard(stage, this, attack_manager);//魔法使い
    player[3] = new Monk(stage, this, attack_manager); //僧侶

    ui->SetPlayerPointer(player);

    if ((arrow_image = LoadGraph("image/Player/arrow.png")) == -1)throw("image/Player/arrow.pngが読み込めません\n");

    OutputDebugString("PlayerManagerコンストラクタ呼ばれました。\n");
}

PlayerManager::~PlayerManager()
{
    for (int i = 0; i < PLAYER_NUM; i++)delete player[i];

    OutputDebugString("PlayerManagerデストラクタが呼ばれました。\n");
}

void PlayerManager::Update(float delta_time)
{
    //先頭キャラ切り替え時の矢印の表示時間
    if ((draw_arrow_time += delta_time) > DRAW_ARROW_TIME)draw_arrow_time = DRAW_ARROW_TIME;

    //死亡キャラの要素数
    int dead_player = -1;


    //更新キャラの前のキャラ情報
    PlayerBase* previous_player = nullptr;

    for (int i = 0; i < PLAYER_NUM; i++)
    {
        //キャラクター更新
        if (player[i]->Update(delta_time, previous_player))
        {
            //キャラが死んだら要素数を入れる
            dead_player = i;
        }

        //現在のキャラの情報を入れる
        previous_player = player[i];


        
    }

    DeadPlayerSorting(dead_player);

    if (Key::KeyDown(KEY_TYPE::L))PlayerSorting();
}

void PlayerManager::DeadPlayerSorting(int dead_player)//死亡プレイヤー並び替え
{
    //死亡キャラがいる場合、入れ替える
    if (dead_player != -1)
    {
        PlayerBase* change_player = player[dead_player];

        for (int i = dead_player; i < PLAYER_NUM; i++)
        {
            if (i == PLAYER_NUM - 1)
            {
                player[i] = change_player;
                if (player[i]->GetIsLeader())draw_arrow_time = 0.0f;
            }
            else player[i] = player[i + 1];
        }
    }
}

void PlayerManager::PlayerSorting()//プレイヤー並び替え
{
    //生きているキャラの数確認
    int alive_player = 0;
    for (int i = 0; i < PLAYER_NUM; i++)
    {
        if (!player[i]->GetIsDead())alive_player++;
    }

    //生きているキャラがいたら、順番を変える
    if (alive_player > 0)
    {
        PlayerBase* change_player = player[0];

        for (int i = 0; i < alive_player; i++)
        {
            if (i == alive_player - 1)player[i] = change_player;
            else player[i] = player[i + 1];
        }
        draw_arrow_time = 0.0f;
    }
}

void PlayerManager::CheckHitDamage(BoxCollider* bc, int attack_power)
{
    for (int i = 0; i < PLAYER_NUM; i++)
    {
        if (player[i]->HitBox(bc))
        {

        }
    }
}

DATA PlayerManager::GetPlayerLocation()const
{
    return player[0]->GetLocation();
}

void PlayerManager::Draw() const
{
    for (int i = PLAYER_NUM - 1; i >= 0; i--)player[i]->Draw();

    if (draw_arrow_time != DRAW_ARROW_TIME)
    {
        DrawRotaGraph(player[0]->GetLocation().x + stage->GetCameraWork(), player[0]->GetLocation().y - 80, 1, 0, arrow_image, TRUE);
    }
}