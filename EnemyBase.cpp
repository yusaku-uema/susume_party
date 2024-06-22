#include"DxLib.h"
#include "EnemyBase.h"


#define SCOPE_OF_ACTIVITY 1000
#define HP_BAR 60
#define HP_BAR_Y1 30
#define HP_BAR_Y2 20

EnemyBase::EnemyBase():CharacterBase({ 1400.0f, 50.0f }, { 50, 50 }, 20, 10, 5, 5)
{
    OutputDebugString("EnemyBaseコンストラクタ呼ばれました。\n");
    dead_boss = false;
}

EnemyBase::~EnemyBase()
{
    OutputDebugString("EnemyBaseデストラクタ呼ばれました。\n");
}
bool EnemyBase::ScopeoOfActivity(float camera_work)
{

    if (spawn_location.x + camera_work + SCOPE_OF_ACTIVITY > location.x + camera_work && spawn_location.x + camera_work - SCOPE_OF_ACTIVITY < location.x +camera_work)
    {
        return false;
    }
    else
    {
       return true;
    }
}

bool EnemyBase::HitDamege(BoxCollider* bc, int attack_power)
{
    if ((hp -= attack_power) <= 0)
    {
        hp = 0;
        is_dead = true;
        attack_manager->AddEnemyAttack(location, DATA{ 0.0f,0.0f }, DATA{ 0.0f,0.0f }, -1.0f, 0, ATTACK_TYPE::EXPLOSION, 3.0f);

        return true;
    }
    return false;
}

bool EnemyBase::GetDeadBoss()
{
    return dead_boss;
}

void EnemyBase::DrawHPBar(const int max_hp) const
{
    DATA draw_location = { location.x + stage->GetCameraWork(), location.y };

    int color = GetColor(7, 255, 0);

    if (hp <= (max_hp / 2))
    {
        color = GetColor(255, 255 * static_cast<float>(hp) / max_hp, 0);
    }
    else
    {
        color = GetColor(7 + 2 * (248 * (1 - static_cast<float>(hp) / max_hp)), 255, 0);
    }

    DrawBox(draw_location.x - HP_BAR / 2, location.y - (radius.y / 2 + HP_BAR_Y1),
        draw_location.x + HP_BAR / 2, location.y - (radius.y / 2 + HP_BAR_Y2), 0x000000, TRUE);
    DrawBox(draw_location.x - HP_BAR / 2, location.y - (radius.y / 2 + HP_BAR_Y1),
        draw_location.x - HP_BAR / 2 + (HP_BAR * (static_cast<float>(hp) / max_hp)), location.y - (radius.y / 2 + HP_BAR_Y2), color, TRUE);
    DrawBox(draw_location.x - HP_BAR / 2, location.y - (radius.y / 2 + HP_BAR_Y1),
        draw_location.x + HP_BAR / 2, location.y - (radius.y / 2 + HP_BAR_Y2), 0x8f917f, FALSE);
}
