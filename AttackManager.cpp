#include"DxLib.h"
#include"AttackManager.h"

AttackManager::AttackManager(class Stage* stage) : stage(stage)
{
    OutputDebugString("AttackManager�R���X�g���N�^�Ă΂�܂����B\n");
}

AttackManager::~AttackManager()
{
    attack.clear();
    attack.shrink_to_fit();

    OutputDebugString("AttackManager�f�X�g���N�^���Ă΂�܂����B\n");
}

void AttackManager::Update(float delta_time)
{
    for (int i = 0; i < attack.size(); i++)
    {
        if (attack[i].Update(delta_time, stage))//�U���̍X�V
        {
            attack.erase(attack.begin() + i);//�U��������
            i--;
        }
    }
}

void AttackManager::AddAttack(DATA location, DATA size, DATA speed, float duration_time, int attack_power, int attack_image)
{
    attack.emplace_back(location, size, speed, duration_time, attack_power, attack_image);
}

void AttackManager::Draw() const
{
    for (int i = 0; i < attack.size(); i++)attack[i].Draw(stage->GetCameraWork());
}