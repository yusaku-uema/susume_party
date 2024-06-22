#pragma once
#include"PlayerManager.h"
#include"Stage.h"

class EnemyBase : public CharacterBase
{
protected:

	int time; //時間
	int image_type; //使う画像の要素指定
	long int animation_time; //画像切替に使う変数

	float distance_moved; //動いた距離
	float attack_speed; //攻撃速度
	float distance; //相手との距離
	float dx, dy; //変化量

	bool direction; //向いている方向
	bool dead_boss;

	DATA spawn_location; //スポーンした座標を覚える

public:
	EnemyBase();
	virtual ~EnemyBase();

	virtual void Update() = 0;
	virtual void Draw()const = 0;

	virtual void DrawHPBar(const int) const;

	bool ScopeoOfActivity(float camera_work); //活動範囲外に出ていないのか

	bool HitDamege(BoxCollider* bc, int attack_power)override;
	bool GetDeadBoss();

};

