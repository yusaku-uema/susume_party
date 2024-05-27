#pragma once
#include"PlayerManager.h"

class EnemyBase : public CharacterBase
{
protected:

	int time; //時間
	int image_type; //使う画像の要素指定
	long int animation_time; //画像切替に使う変数

public:
	EnemyBase();
	~EnemyBase();

};

