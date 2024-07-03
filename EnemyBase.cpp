#include"DxLib.h"
#include "EnemyBase.h"
#include"Stage.h"

#define SCOPE_OF_ACTIVITY_X 300.0f

#define HP_BAR_X 60.0f
#define HP_BAR_Y 10.0f

#define PI 3.14159265358979323846 // pi

EnemyBase::EnemyBase(DATA location, DATA size, int hp, int mp, int attack_power, int enemy_image[ENEMY_STATE::END][5]) : 
CombatCharacterBase(location, size, hp, mp, attack_power, 5),
enemy_state(ENEMY_STATE::NORMAL), spawn_location(location), enemy_control_time(0.0f)
{
    for (int i = 0; i < ENEMY_STATE::END; i++)
    {
        for (int j = 0; j < 5; j++)this->enemy_image[i][j] = enemy_image[i][j];
    }

    OutputDebugString("EnemyBaseコンストラクタ呼ばれました。\n");
}

EnemyBase::~EnemyBase()
{
    OutputDebugString("EnemyBaseデストラクタ呼ばれました。\n");
}
bool EnemyBase::ScopeoOfActivity()const
{
    if ((location.x > (spawn_location.x + SCOPE_OF_ACTIVITY_X)) && (!is_facing_left))return true;
    return ((location.x < (spawn_location.x - SCOPE_OF_ACTIVITY_X)) && (is_facing_left));
}

bool EnemyBase::HitDamege(class BoxCollider* bc, int attack_power)
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

void EnemyBase::Draw() const
{
    DATA draw_location = { location.x + stage->GetCameraWork(), location.y };

    if ((draw_location.x > -radius.x) && (draw_location.x < SCREEN_SIZE_X + radius.x))
    {
        Draw(draw_location);
        DrawHpBar(draw_location);
    }
}

void EnemyBase::DrawHpBar(DATA draw_location) const
{
    float hp_ratio = (float)hp / max_hp;
    int color_ratio = (255 * hp_ratio);
    int color = GetColor(255 - (color_ratio * 2), 255, 0);
    if (hp_ratio <= 0.5f)color = GetColor(255, (color_ratio * 2), 0);

    int start_hp_bar_x = draw_location.x - (HP_BAR_X / 2);
    int start_hp_bar_y = draw_location.y - 70.0f;

    DrawBox(start_hp_bar_x, start_hp_bar_y, start_hp_bar_x + HP_BAR_X, start_hp_bar_y + HP_BAR_Y, 0x000000, TRUE);
    DrawBox(start_hp_bar_x, start_hp_bar_y, start_hp_bar_x + (hp_ratio * HP_BAR_X), start_hp_bar_y + HP_BAR_Y, color, TRUE);
    DrawBox(start_hp_bar_x, start_hp_bar_y, start_hp_bar_x + HP_BAR_X, start_hp_bar_y + HP_BAR_Y, 0xffffff, FALSE);
}

//-----------------------------------
//敵の状態の変更
//-----------------------------------
void EnemyBase::SetEnemyState(ENEMY_STATE enemy_state)
{
    this->enemy_state = enemy_state;
    draw_image_num = 0;
    image_change_time = 0.0f;
    enemy_control_time = 0.0f;
    speed = { 0.0f,0.0f };
}

//-----------------------------------
//敵の状態の取得
//-----------------------------------
EnemyBase::ENEMY_STATE EnemyBase::GetEnemyState()const
{
    return enemy_state;
}

//-----------------------------------
//キャラクター追跡
//-----------------------------------
DATA EnemyBase::TargetTracking(DATA target_location, float speed)const
{
    float dx = target_location.x - location.x;
    float dy = target_location.y - location.y;
    float distance = sqrt(dx * dx + dy * dy); // ユークリッド距離の計算（平方根を取る）

    return{ (dx / distance) * speed,(dy / distance) * speed };
}