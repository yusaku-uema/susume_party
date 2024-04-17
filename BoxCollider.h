#pragma once
#include"define.h"

class BoxCollider
{
protected:
	DATA location;//�I�u�W�F�N�g�̍��W
	DATA radius;//�I�u�W�F�N�g�̔��a

public:

	BoxCollider(DATA location, DATA size);
	~BoxCollider();

	bool HitBox(BoxCollider* bc)const;
	bool HitBox(DATA location, DATA radius)const;
	DATA GetLocation(void)const;
	DATA GetRadius(void)const;
};

