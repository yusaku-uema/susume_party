#pragma once
#include"define.h"

class BoxCollider
{
protected:
	DATA location;//オブジェクトの座標
	DATA radius;//オブジェクトの半径

public:

	BoxCollider(DATA location, DATA size);
	~BoxCollider();

	bool HitBox(BoxCollider* bc)const;
	bool HitBox(DATA location, DATA radius)const;
	DATA GetLocation(void)const;
	DATA GetRadius(void)const;
};

