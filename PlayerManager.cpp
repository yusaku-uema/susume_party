#include"DxLib.h"
#include"Key.h"
#include"PlayerManager.h"

PlayerManager::PlayerManager()
{
    player[0] = new PlayerBase(0x0000ff);//勇者
    player[1] = new PlayerBase(0xff0000);//戦士
    player[2] = new PlayerBase(0xff00ff);//魔法使い
    player[3] = new PlayerBase(0x00ff00);//僧侶

    OutputDebugString("PlayerManagerコンストラクタ呼ばれました。\n");
}

PlayerManager::~PlayerManager()
{
    for (int i = 0; i < PLAYER_NUM; i++)delete player[i];
    delete[] player;

    OutputDebugString("PlayerManagerデストラクタが呼ばれました。\n");
}

void PlayerManager::Update(float delta_time, class Stage* stage)
{
    if (Key::KeyDown(KEY_TYPE::L))PlayerSorting();

    for (int i = 0; i < PLAYER_NUM; i++)
    {
        if(i == 0)player[i]->Update(delta_time, stage, nullptr);
        else player[i]->Update(delta_time, stage, player[i - 1]);
    }
}

void PlayerManager::PlayerSorting()//プレイヤー並び替え
{
    PlayerBase* player = this->player[0];
    for (int i = 0; i < PLAYER_NUM; i++)
    {
        if(i == PLAYER_NUM - 1)this->player[i] = player;
        else this->player[i] = this->player[i + 1];
    }
}

DATA PlayerManager::GetPlayerLocation()const
{
    return player[0]->GetLocation();
}

void PlayerManager::Draw(float camera_work) const
{
    for (int i = 0; i < PLAYER_NUM; i++)player[i]->Draw(camera_work);
}