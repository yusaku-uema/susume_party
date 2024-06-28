#pragma once
#include"CombatCharacterBase.h"

class EnemyBase : public CombatCharacterBase
{
protected:

	enum ENEMY_STATE//�G�̏��
	{
		NORMAL,//�ʏ�
		PREPARING_ATTACK,//�U������
		ATTACK, //�U��
		AFTER_ATTACK,//�U����
	};

	ENEMY_STATE enemy_state;//�G�̏��

	float enemy_control_time;//�G�̐���p����
	int enemy_image[4][5];
	
	void ChangeEnemyState(ENEMY_STATE enemy_state);
	
	DATA spawn_location; //�X�|�[���������W���o����

public:
	EnemyBase(DATA location, DATA size, int hp, int mp, int attack_power);
	virtual ~EnemyBase();

	virtual void Update(float delta_time) = 0;
	virtual void Draw(DATA draw_location)const = 0;
	void Draw()const;

	virtual void DrawHpBar(DATA draw_location) const;

	bool ScopeoOfActivity(float camera_work); //�����͈͊O�ɏo�Ă��Ȃ��̂�

	bool HitDamege(BoxCollider* bc, int attack_power)override;
	
};

