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

private:

	ENEMY_STATE enemy_state;//敵の状態
	DATA spawn_location; //スポーンした座標を覚える
	void DrawHpBar(DATA draw_location) const;

protected:

	int enemy_image[ENEMY_STATE::END][5];

	float enemy_control_time;//敵の制御用時間
	
	void SetEnemyState(ENEMY_STATE enemy_state);
	ENEMY_STATE GetEnemyState()const;
	
	DATA TargetTracking(DATA target_location, float speed)const;

	bool ScopeoOfActivity()const; //活動範囲外に出たか？

	virtual void Draw(DATA draw_location)const = 0;

public:

	EnemyBase(DATA location, DATA size, int hp, int mp, int attack_power, int enemy_image[ENEMY_STATE::END][5]);
	virtual ~EnemyBase();

	virtual void Update(float delta_time) = 0;
	void Draw()const;

	bool HitDamege(class BoxCollider* bc, int attack_power)override;
	
};

