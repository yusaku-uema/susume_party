#pragma once

#define SCREEN_WIDTH 1280 //横画面サイズ
#define SCREEN_HEIGHT 720 //縦画面サイズ

#define STAGE_BLOCK_NUM_Y 15 //ステージの縦ブロックの数
#define STAGE_BLOCK_NUM_X 120 //ステージの横ブロックの数

#define BLOCK_TYPE_NUM 8//ブロックの種類

#define BLOCK_SIZE 36.0f //ブロックのサイズ

#define GRAVITY 0.25f //重力の大きさ
#define FALL_SPEED 5.0f//落下速度の最大値

struct DATA //座標,大きさ,スピードなどに使う
{
    float x, y;
};

enum class BLOCK_TYPE
{
    GRASSLAND_BLOCK = 1,//草原ブロック
    SOIL_BLOCK,//土ブロック

};