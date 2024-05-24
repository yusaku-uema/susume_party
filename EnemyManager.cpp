#include"DxLib.h"

#include"EnemyManager.h"

#include"Slime.h"
#include"Bird.h"
#include"Flower.h"
#include"Fairy.h"

//#include"Stage.h"

#define DRAW_ARROW_TIME 2.0f//�v���C���[���w�����̕\������

EnemyManager::EnemyManager(class Stage* stage, class PlayerManager* player_manager)
{
    slime = new Slime(stage, player_manager);
    bird = new Bird(stage, player_manager);
    flower = new Flower(stage, player_manager);
    fairy = new Fairy(stage, player_manager);

    OutputDebugString("EnemyManager�R���X�g���N�^�Ă΂�܂����B\n");
}

EnemyManager::~EnemyManager()
{
    delete slime;
    delete bird;
    delete flower;

    OutputDebugString("EnemyManager�f�X�g���N�^���Ă΂�܂����B\n");
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