#include"DxLib.h"
#include"Key.h"
#include"PlayerManager.h"
#include"Hero.h"
#include"Warrior.h"
#include"Wizard.h"
#include"Monk.h"

#define DRAW_ARROW_TIME 2.0f//プレイヤーを指す矢印の表示時間

PlayerManager::PlayerManager(class Stage* stage, Ui* ui) : draw_arrow_time(0.0f), alive_player(PLAYER_NUM)
{
    player[0] = new Hero(stage);//勇者
    player[1] = new Warrior(stage);//戦士
    player[2] = new Wizard(stage);//魔法使い
    player[3] = new Monk(stage); //僧侶

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
    if (draw_arrow_time != DRAW_ARROW_TIME)
    {
        if ((draw_arrow_time += delta_time) > DRAW_ARROW_TIME)draw_arrow_time = DRAW_ARROW_TIME;
    }

    int alive_player = 0;

    for (int i = 0; i < PLAYER_NUM; i++)
    {
        if (i == 0)player[i]->Update(delta_time, nullptr);
        else player[i]->Update(delta_time, player[i - 1]);

        if (!player[i]->GetIsDead())alive_player++;
    }

    if (this->alive_player != alive_player)
    {
        this->alive_player = alive_player;
        DeadPlayerSorting();
    }

    if (Key::KeyDown(KEY_TYPE::L))PlayerSorting();
}

void PlayerManager::DeadPlayerSorting()//死亡プレイヤー並び替え
{
    PlayerBase* player = nullptr;

    for (int i = 0; i < PLAYER_NUM; i++)
    {
        if (player == nullptr)
        {
            if (this->player[i]->GetIsDead())player = this->player[i];
        }

        if(player != nullptr)
        {
            if (i == PLAYER_NUM - 1)
            {
                this->player[i] = player;
                if (this->player[i]->GetIsLeader())draw_arrow_time = 0.0f;
            }
            else this->player[i] = this->player[i + 1];
        }
    }
}

void PlayerManager::PlayerSorting()//プレイヤー並び替え
{
    if (alive_player > 0)
    {
        PlayerBase* player = this->player[0];

        for (int i = 0; i < alive_player; i++)
        {
            if (i == alive_player - 1)this->player[i] = player;
            else this->player[i] = this->player[i + 1];
        }
        draw_arrow_time = 0.0f;
    }
}

DATA PlayerManager::GetPlayerLocation()const
{
    return player[0]->GetLocation();
}

void PlayerManager::Draw(float camera_work) const
{
    for (int i = PLAYER_NUM - 1; i >= 0; i--)player[i]->Draw(camera_work);
    if (draw_arrow_time != DRAW_ARROW_TIME)DrawRotaGraph(player[0]->GetLocation().x + camera_work, player[0]->GetLocation().y - 80, 1, 0, arrow_image, TRUE);
}