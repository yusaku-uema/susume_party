#include"DxLib.h"
#include"Player.h"
#include"Key.h"

#define PLAYER_SIZE 30.0f//サイズ
#define WALK_SPEED 1.5f//1フレームで進む速さ
#define JUMP_SPEED 8.0f//1フレームでジャンプする高さ
#define ACCELERATION 0.1f//歩く時の加速

Player::Player() : CharacterBase({ 90.0f, 200.0f }, { PLAYER_SIZE, PLAYER_SIZE }, 20, 10, 5, 5),
is_walking(false), is_jump(false), is_facing_left(false)
{
    OutputDebugString("Playerコンストラクタ呼ばれました。\n");
}

Player::~Player()
{
    OutputDebugString("Playerデストラクタが呼ばれました。\n");
}

void Player::Update(float delta_time, Stage* stage)
{
    //x座標の更新
    if (Key::GetStickAngle(KEY_TYPE::L).x < 0.0f)//左が押されてるなら左に進む
    {
        if ((speed.x -= ACCELERATION) < -WALK_SPEED) speed.x = -WALK_SPEED;
    }
    else if (Key::GetStickAngle(KEY_TYPE::L).x > 0.0f)//右が押されてるなら右に進む
    {
        if ((speed.x += ACCELERATION) > WALK_SPEED)speed.x = WALK_SPEED;
    }
    else//何も押されていない時は、徐々にスピードを落とす
    {
        if (speed.x < 0.0f)
        {
            if ((speed.x += ACCELERATION) > 0.0f) speed.x = 0.0f;
        }
        else if (speed.x > 0.0f)
        {
            if ((speed.x -= ACCELERATION) < 0.0f)speed.x = 0.0f;
        }
    }

    location.x += speed.x;//座標の加算

    is_walking = true;//歩いている変数をtrueにする
    if (speed.x < 0.0f)is_facing_left = true;//左に進んでいるならis_facing_leftをtrueにする
    else if (speed.x > 0.0f)is_facing_left = false;//右に進んでいるならis_facing_leftをfalseにする
    else is_walking = false;//どちらにも進んでいないなら歩いている変数をfalseにする

    if (stage->HitBlock(this))//もしブロックに当たっていたら
    {
        location.x = roundf(location.x);//座標を整数値にする
        while (stage->HitBlock(this))location.x -= (speed.x / fabsf(speed.x));//ブロックに当たっている間、進行方向とは逆に進める
    }

    //y座標の更新
    speed.y += GRAVITY;//重力の加算
    if (speed.y > FALL_SPEED)speed.y = FALL_SPEED;//重力が一定数を越えないようにする

    location.y += speed.y;//座標の加算

    if (stage->HitBlock(this))//もしブロックに当たっていたら（地面か頭に当たっている）
    {
        location.y = roundf(location.y);//座標を整数値にする
        while (stage->HitBlock(this))location.y -= (speed.y / fabsf(speed.y));//ブロックに当たっている間、進行方向とは逆に進める

        if (speed.y > 0.0f)//地面に当たっている
        {
            is_jump = false;//ジャンプ状態をfalseにする
            if (Key::KeyDown(KEY_TYPE::A))speed.y = -JUMP_SPEED;//Aボタンでジャンプ
            else speed.y = 0.0f;//Aボタンが押されてなければy座標のスピードを0にする
        }
        else//頭にブロックが当たっている
        {
            speed.y = 0.0f;//Yのスピードを0にする。
        }
    }
    else is_jump = true;//ブロックに当たっていないとき（空中にいるとき）ジャンプにする

}

void Player::Draw() const
{
    DrawBox(location.x - radius.x, location.y - radius.y, location.x + radius.x, location.y + radius.y, 0xffffff, TRUE);
}