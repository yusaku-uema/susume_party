#include"DxLib.h"
#include"Key.h"
#include"PlayerManager.h"
#include"Hero.h"
#include"Warrior.h"
#include"Wizard.h"
#include"Monk.h"


PlayerManager::PlayerManager()
{
    player[0] = new Hero();//勇者
    player[1] = new Warrior();//戦士
    player[2] = new Wizard();//魔法使い
    player[3] = new Monk(); //僧侶

    OutputDebugString("PlayerManagerコンストラクタ呼ばれました。\n");
}

PlayerManager::~PlayerManager()
{
    for (int i = 0; i < PLAYER_NUM; i++)delete player[i];

    attack.clear();
    attack.shrink_to_fit();

    OutputDebugString("PlayerManagerデストラクタが呼ばれました。\n");
}

void PlayerManager::Update(float delta_time, class Stage* stage)
{
    for (int i = 0; i < attack.size(); i++)
    {
        if (attack[i].Update(delta_time))//攻撃の更新
        {
            attack.erase(attack.begin() + i);//攻撃を消す
            i--;
        }
    }

    if (Key::KeyDown(KEY_TYPE::L))PlayerSorting();

    for (int i = 0; i < PLAYER_NUM; i++)
    {
        if (i == 0)player[i]->Update(delta_time, stage, nullptr, this);
        else player[i]->Update(delta_time, stage, player[i - 1], this);
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

void PlayerManager::AddAttack(DATA location, DATA size, DATA speed, float duration_time, int attack_power, int attack_image)
{
    attack.emplace_back(location, size, speed, duration_time, attack_power, attack_image);
}

DATA PlayerManager::GetPlayerLocation()const
{
    return player[0]->GetLocation();
}

void PlayerManager::Draw(float camera_work) const
{
    for (int i = 0; i < attack.size(); i++)attack[i].Draw(camera_work);
    for (int i = 0; i < PLAYER_NUM; i++)player[i]->Draw(camera_work);
}