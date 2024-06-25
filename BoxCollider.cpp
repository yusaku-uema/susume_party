#include"dxlib.h"
#include"BoxCollider.h"

BoxCollider::BoxCollider(DATA location, DATA size) : location(location), radius(DATA{ size.x / 2, size.y / 2 })
{
    OutputDebugString("BoxColliderコンストラクタが呼ばれました。\n");
}

BoxCollider::~BoxCollider()
{
    OutputDebugString("BoxColliderデストラクタが呼ばれました。\n");
}

bool BoxCollider::HitBox(BoxCollider* bc)const
{
    float sx1 = location.x - radius.x;
    float sx2 = location.x + radius.x;
    float sy1 = location.y - radius.y;
    float sy2 = location.y + radius.y;

    float dx1 = bc->location.x - bc->radius.x;
    float dx2 = bc->location.x + bc->radius.x;
    float dy1 = bc->location.y - bc->radius.y;
    float dy2 = bc->location.y + bc->radius.y;

    //重なっていれば当たり
    return (sx1 < dx2 && dx1 < sx2 && sy1 < dy2 && dy1 < sy2);
}

DATA BoxCollider::GetLocation()const
{
    return location;
}