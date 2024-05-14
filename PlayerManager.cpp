#include"DxLib.h"
#include"Key.h"
#include"PlayerManager.h"
#include"Hero.h"
#include"Warrior.h"
#include"Wizard.h"
#include"Monk.h"


PlayerManager::PlayerManager()
{
    player[0] = new Hero();//�E��
    player[1] = new Warrior();//��m
    player[2] = new Wizard();//���@�g��
    player[3] = new Monk(); //�m��

    OutputDebugString("PlayerManager�R���X�g���N�^�Ă΂�܂����B\n");
}

PlayerManager::~PlayerManager()
{
    for (int i = 0; i < PLAYER_NUM; i++)delete player[i];

    OutputDebugString("PlayerManager�f�X�g���N�^���Ă΂�܂����B\n");
}

void PlayerManager::Update(float delta_time, class Stage* stage)
{
    if (Key::KeyDown(KEY_TYPE::L))PlayerSorting();

    for (int i = 0; i < PLAYER_NUM; i++)
    {
        if (i == 0)player[i]->Update(delta_time, stage, nullptr);
        else player[i]->Update(delta_time, stage, player[i - 1]);
    }
}

void PlayerManager::PlayerSorting()//�v���C���[���ёւ�
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