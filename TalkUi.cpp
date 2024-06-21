#include "TalkUi.h"
#include "DxLib.h"
#include "Key.h"

TalkUi::TalkUi()
    : hero_frame(0), hero_frame_count(0), hero_x(200), hero_y(400), hero_direction(-1), is_moving(false) // 初期化リストでフレーム関連の変数を初期化
{
    // メッセージ作成
    message = new Message("txt/comment.txt");
}

TalkUi::~TalkUi()
{
    delete message; // メッセージの削除
}

void TalkUi::Initialize()
{
    king_image = LoadGraph("image/CharTalk/king.png");
    if (king_image == -1)
    {
        throw("image/CharTalk/king.pngが読み込めませんでした。\n");
    }
    background_image = LoadGraph("image/CharTalk/background.png");
    if (background_image == -1)
    {
        throw("image/CharTalk/background.pngが読み込めません\n");
    }

    // 勇者の画像を分割して読み込み
    if (LoadDivGraph("image/Player/Hero/walk.png", 5, 5, 1, 50, 50, hero_images) == -1)
    {
        throw("image/Player/Hero/walk.pngが読み込めません\n");
    }
    if (LoadDivGraph("image/Player/Hero/wait.png", 5, 5, 1, 50, 50, hero_standby) == -1)
    {
        throw("image/Player/Hero/wait.pngが読み込めません\n");
    }
}

void TalkUi::Finalize()
{
    DeleteGraph(king_image);
    DeleteGraph(background_image);
    for (int i = 0; i < 5; ++i)
    {
        DeleteGraph(hero_images[i]); // 勇者の歩行画像の削除
        DeleteGraph(hero_standby[i]); // 勇者の待機画像の削除
    }
}

SCENE_TYPE TalkUi::Update(float delta_time)
{
    if (Key::KeyDown(KEY_TYPE::B))
    {
        return SCENE_TYPE::MAIN;
    }

    // メッセージの更新処理を呼び出し、true が返されたらシーン遷移
    if (message->Update(delta_time))
    {
        return SCENE_TYPE::MAIN;
    }

    // 入力フラグ
    is_moving = false;

    // 勇者の位置を更新
    int move_speed = 5;
    int stick_move_speed = 2; // スティック操作時の移動速度

    // 十字キーの入力処理
    if (Key::KeyPressed(KEY_TYPE::LEFT))
    {
        hero_x -= move_speed;
        hero_direction = -1;
        is_moving = true;
    }
    if (Key::KeyPressed(KEY_TYPE::RIGHT))
    {
        hero_x += move_speed;
        hero_direction = 1;
        is_moving = true;
    }
    // 左スティックの入力処理
    DATA l_stick = Key::GetStickAngle(KEY_TYPE::L);
    if (l_stick.x < -500)
    {
        hero_x -= stick_move_speed;
        hero_direction = -1;
        is_moving = true;
    }
    if (l_stick.x > 500)
    {
        hero_x += stick_move_speed;
        hero_direction = 1;
        is_moving = true;
    }

    // 勇者のアニメーションフレームを更新
    hero_frame_count++;
    if (is_moving)
    {
        if (hero_frame_count >= 10) // 10フレームごとにアニメーションを更新
        {
            hero_frame_count = 0;
            hero_frame = (hero_frame + 1) % 4; // 0から3のフレームを循環
        }
    }
    else
    {
        if (hero_frame_count >= 15) // 15フレームごとに待機アニメーションを更新
        {
            hero_frame_count = 0;
            hero_frame = (hero_frame + 1) % 4; // 0から3のフレームを循環
        }
    }

    // 勇者の位置を画面内に制限
    int hero_width, hero_height;
    GetGraphSize(hero_images[0], &hero_width, &hero_height);

    if (hero_x < 0) hero_x = 0;
    if (hero_x > 1280 - hero_width * 3) hero_x = 1280 - hero_width * 3;
    if (hero_y < 0) hero_y = 0;
    if (hero_y > 720 - hero_height * 3) hero_y = 720 - hero_height * 3; // 720は画面の高さ

    return GetNowScene();
}

void TalkUi::Draw() const
{
    DrawGraph(0, 0, background_image, TRUE);

    int king_width, king_height;
    GetGraphSize(king_image, &king_width, &king_height);
    DrawExtendGraph(50, 400, 50 + king_width * 3, 400 + king_height * 3, king_image, TRUE); // スケールファクターは3

    // 勇者の画像を左右反転して描画
    int hero_width, hero_height;
    GetGraphSize(hero_images[0], &hero_width, &hero_height);
    const int* current_hero_images = is_moving ? hero_images : hero_standby;
    if (hero_direction == 1)
    {
        DrawExtendGraph(hero_x, hero_y, hero_x + hero_width * 3, hero_y + hero_height * 3, current_hero_images[hero_frame], TRUE); // スケールファクターは3
    }
    else
    {
        DrawExtendGraph(hero_x + hero_width * 3, hero_y, hero_x, hero_y + hero_height * 3, current_hero_images[hero_frame], TRUE); // スケールファクターは3
    }

    message->Draw();
}

SCENE_TYPE TalkUi::GetNowScene() const
{
    return SCENE_TYPE::TALKUI;
}