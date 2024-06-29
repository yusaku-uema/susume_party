#pragma once
#include"CombatCharacterBase.h"

class EnemyBase : public CombatCharacterBase
{
public:

	enum ENEMY_STATE//敵の状態
	{
		NORMAL,//通常
		PREPARING_ATTACK,//攻撃準備
		ATTACK, //攻撃
		AFTER_ATTACK,//攻撃後

		END
	};

protected:

	ENEMY_STATE enemy_state;//敵の状態

	float enemy_control_time;//敵の制御用時間
	int enemy_image[ENEMY_STATE::END][5];
	
	void ChangeEnemyState(ENEMY_STATE enemy_state);
	
	DATA spawn_location; //スポーンした座標を覚える

public:

	EnemyBase(DATA location, DATA size, int hp, int mp, int attack_power, int enemy_image[ENEMY_STATE::END][5]);
	virtual ~EnemyBase();

	virtual void Update(float delta_time) = 0;
	virtual void Draw(DATA draw_location)const = 0;
	void Draw()const;

	virtual void DrawHpBar(DATA draw_location) const;

	bool ScopeoOfActivity(float camera_work); //活動範囲外に出ていないのか

	bool HitDamege(BoxCollider* bc, int attack_power)override;
	
};

