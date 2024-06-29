#include"DxLib.h"
#include"EnemyManager.h"

//�U�R�G
#include"Slime.h"
#include"Bird.h"
#include"Flower.h"
#include"Fairy.h"

//�{�X
#include"BlackMage.h"

#define DRAW_ARROW_TIME 2.0f//�v���C���[���w�����̕\������

EnemyManager::EnemyManager() : dead_boss(false)
{
    for (int i = 0; i < ENEMY_TYPE::END; i++)
    {
        for (int j = 0; j < EnemyBase::ENEMY_STATE::END; j++)
        {
            for (int k = 0; k < 5; k++)enemy_image[i][j][k] = NULL;
        }
    }
    
    //�t�����[�摜
    if (LoadDivGraph("image/Enemy/flower/normal.png", 3, 3, 1, 80, 80, enemy_image[ENEMY_TYPE::FLOWER][EnemyBase::ENEMY_STATE::NORMAL]) == -1)throw("image/Enemy/flower/normal.png\n");
    if (LoadDivGraph("image/Enemy/flower/preparingattack.png", 1, 1, 1, 80, 80, enemy_image[ENEMY_TYPE::FLOWER][EnemyBase::ENEMY_STATE::PREPARING_ATTACK]) == -1)throw("image/Enemy/flower/preparingattack.png\n");
    if (LoadDivGraph("image/Enemy/flower/attack.png", 3, 3, 1, 80, 80, enemy_image[ENEMY_TYPE::FLOWER][EnemyBase::ENEMY_STATE::ATTACK]) == -1)throw("image/Enemy/flower/attack.png\n");

    OutputDebugString("EnemyManager�R���X�g���N�^�Ă΂�܂����B\n");
}

EnemyManager::~EnemyManager()
{
    for (int i = 0; i < ENEMY_TYPE::END; i++)
    {
        for (int j = 0; j < EnemyBase::ENEMY_STATE::END; j++)
        {
            for (int k = 0; k < 5; k++)DeleteGraph(enemy_image[i][j][k]);
        }
    }

    for (int i = 0; i < enemy.size(); i++)delete enemy[i];
    enemy.clear();
    enemy.shrink_to_fit();

    OutputDebugString("EnemyManager�f�X�g���N�^���Ă΂�܂����B\n");
}

void EnemyManager::Initialize(class Stage* stage, class PlayerManager* player_manager, class AttackManager* attack_manager)
{
    this->stage = stage;
    this->player_manager = player_manager;
    this->attack_manager = attack_manager;

    enemy.emplace_back(new Flower({ 600, 400 }, enemy_image[ENEMY_TYPE::FLOWER], stage, player_manager, attack_manager));

    SetEnemy();
}

void EnemyManager::Update(float delta_time)
{
    for (int i = 0; i < enemy.size(); i++)
    {
        enemy[i]->Update(delta_time);

        //���񂾏ꍇ
        if (enemy[i]->GetIsDead())
        {
            //���̓G��ǂ��Ă����e�̒ǐՂ���߂�
            attack_manager->DeleteTargetPointer(enemy[i]);

            enemy.erase(enemy.begin() + i);//�G������
            i--;
        }
    }
}

bool EnemyManager::CheckHitDamage(class BoxCollider* bc, int attack_power)
{
    for (int i = 0; i < enemy.size(); i++)
    {
        if (enemy[i]->HitBox(bc))
        {
            enemy[i]->HitDamege(bc, attack_power);
            return true;
        }
    }
    return false;
}

bool EnemyManager::NextTransition()
{
    return dead_boss;
}

class BoxCollider* EnemyManager::GetEnemyData(int enemy_num)const
{
    if ((enemy.size() != 0) && (enemy_num < enemy.size()) && (enemy_num >= 0))
    {
        return enemy[enemy_num];
    }
    return nullptr;
}

int EnemyManager::GetEnemyNum()const
{
    return enemy.size();
}

void EnemyManager::Draw() const
{
    for (int i = 0; i < enemy.size(); i++)
    {
        //DrawFormatString(enemy[i]->GetLocation().x + stage->GetCameraWork(), enemy[i]->GetLocation().y - 50, 0xffffff, "%d", i);
        enemy[i]->Draw();
    }
}

void EnemyManager::SpawnEnemy(ENEMY_TYPE enemy_type, DATA location)
{
    switch (enemy_type)
    {
    case ENEMY_TYPE::SLIME:
        //enemy.emplace_back(new Slime(stage, player_manager, attack_manager, location));
        break;
    case ENEMY_TYPE::FLOWER:
        enemy.emplace_back(new Flower(location, enemy_image[enemy_type], stage, player_manager, attack_manager));
        break;
    case ENEMY_TYPE::BIRD:
        //enemy.emplace_back(new Bird(stage, player_manager, attack_manager,location));
        break;
    case ENEMY_TYPE::FAIRY:
        //enemy.emplace_back(new Fairy(stage, player_manager, attack_manager, location));
        break;
    case ENEMY_TYPE::BLACKMAGE:
        //enemy.emplace_back(new BlackMage(stage, player_manager, attack_manager, location));
        break;

    default:
        break;
    }
}

void EnemyManager::SetEnemy()
{
    FILE* enemy_data = nullptr;//�X�e�[�W�ǂݍ���

    errno_t error_enemy_data = fopen_s(&enemy_data, "data/enemyplacement.txt", "r");
    if (error_enemy_data != 0)throw("data/enemyplacement.txt���ǂݍ��߂܂���\n");//�G���[�`�F�b�N


    //�G�l�~�[��z�u����
    for (int i = 0; i < STAGE_BLOCK_NUM_Y; i++)//�c�̌J��Ԃ�
    {
        for (int j = 0; j < STAGE_BLOCK_NUM_X; j++)//���̌J��Ԃ�
        {
            //�G�l�~�[�̎��
            int enemy_type;
            fscanf_s(enemy_data, "%d", &enemy_type);

            //�G�l�~�[�̐���
            if (enemy_type != -1)
            {
                DATA location = { (j * BLOCK_SIZE) + (BLOCK_SIZE / 2) - BLOCK_SIZE , i * BLOCK_SIZE + (BLOCK_SIZE / 2) };
                
                SpawnEnemy(static_cast<ENEMY_TYPE>(enemy_type), location);
                
            }
        }
    }
    fclose(enemy_data);
}
