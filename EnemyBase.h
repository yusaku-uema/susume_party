#pragma once
#include"PlayerManager.h"

class EnemyBase : public CharacterBase
{
protected:

	int time; //����
	int image_type; //�g���摜�̗v�f�w��
	long int animation_time; //�摜�ؑւɎg���ϐ�

public:
	EnemyBase();
	~EnemyBase();

};

