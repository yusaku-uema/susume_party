#pragma once
#include"PlayerManager.h"

class EnemyBase : public CharacterBase
{
protected:

	int time; //����
	int image_type; //�g���摜�̗v�f�w��
	long int animation_time; //�摜�ؑւɎg���ϐ�

	float distance_moved; //����������
	float attack_speed; //�U�����x
	float distance; //����Ƃ̋���
	float dx, dy; //�ω���

	bool move_left; //���ɓ���
	bool direction; //�����Ă������

public:
	EnemyBase();
	~EnemyBase();

	virtual void Update() = 0;
	virtual void Draw()const = 0;

	bool HitDamege(int attack_power)override;

};

