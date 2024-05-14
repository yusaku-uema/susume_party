#include"DxLib.h"
#include"AttackManager.h"

AttackManager::AttackManager()
{
    
    OutputDebugString("AttackManagerコンストラクタ呼ばれました。\n");
}

AttackManager::~AttackManager()
{
    attack.clear();
    attack.shrink_to_fit();

    OutputDebugString("AttackManagerデストラクタが呼ばれました。\n");
}

void AttackManager::Update(float delta_time, class Stage* stage)
{
    for (int i = 0; i < attack.size(); i++)
    {
        if (attack[i].Update(delta_time))//攻撃の更新
        {
            attack.erase(attack.begin() + i);//攻撃を消す
            i--;
        }
    }
}

void AttackManager::AddAttack(DATA location, DATA size, DATA speed, float duration_time, int attack_power, int attack_image)
{
    attack.emplace_back(location, size, speed, duration_time, attack_power, attack_image);
}

void AttackManager::Draw(float camera_work) const
{
    for (int i = 0; i < attack.size(); i++)attack[i].Draw(camera_work);
}