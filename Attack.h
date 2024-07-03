#pragma once
#include"BoxCollider.h"
#include"Stage.h"

class Attack : public BoxCollider
{
private:
    BoxCollider* target;//追跡相手

    int* attack_image;//攻撃画像
    int image_num;//画像の数

    float image_change_time;//画像切り替え時間
    int draw_image_num;//表示中の画像
    float image_size;//画像サイズ（画像倍率）

    int attack_power;//攻撃力
    DATA speed;//スピード
    float duration_time;//攻撃継続時間
    int angle;//画像の角度

    bool delete_hit_stage;//ステージに当たった時に消すか？
    bool delete_hit_chara;//キャラクターに当たった時に消すか？

    void TargetTracking(); //追尾

public:
    Attack(DATA location, DATA size, DATA speed, BoxCollider* target,bool delete_hit_stage, bool delete_hit_chara,
        float duration_time, int attack_power, int* attack_image, int image_num, float image_size);
    ~Attack();

    bool Update(float delta_time, class Stage* stage, class PlayerManager* player_manager, class EnemyManager* enemy_manager);
    void Draw(float camera_work)const;

    int GetAttackPower()const;
    int GetImageSize()const;

    void DeleteTargetPointer(BoxCollider* target);//追跡中のキャラのポインターの消去
};