#pragma once

#define FONT_SIZE 35 // 文字の大きさ

#define SCREEN_SIZE_X 1280 //横画面サイズ
#define SCREEN_SIZE_Y 720 //縦画面サイズ

#define HALF_SCREEN_SIZE_X 640
#define HALF_SCREEN_SIZE_Y 360

#define STAGE_BLOCK_NUM_Y 15 //ステージの縦ブロックの数
#define STAGE_BLOCK_NUM_X 276 //ステージの横ブロックの数

#define BLOCK_TYPE_NUM 17//ブロックの種類

#define BLOCK_SIZE 36.0f //ブロックのサイズ

#define GRAVITY 0.2f //重力の大きさ
#define FALL_SPEED 5.0f//落下速度の最大値

#define ENEMY_EXPLOSION_SIZE 5

struct DATA //座標,大きさ,スピードなどに使う
{
    float x, y;
};

enum class PLAYER_JOB//プレイヤー職業
{
    HERO,//勇者
    WARRIOR,//戦士
    WIZARD,//魔法使い
    MONK//僧侶
};