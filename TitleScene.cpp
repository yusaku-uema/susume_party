#include "TitleScene.h"
#include "DxLib.h"
#include "Key.h"

// スクロールスピード
#define SCROLL_SPEED 1
// 画面の幅と高さ
#define SCREEN_SIZE_X 640
#define SCREEN_SIZE_Y 650

// 背景画像の幅と高さ
#define BACKGROUND_WIDTH 1280
#define BACKGROUND_HEIGHT 720

#define INPUT_ACCEPTANCE_TIME 10

// 初期化
int TitleScene::scrollX = 0;
int TitleScene::logoX = 1300; // ロゴの初期位置を画面右端に設定
int TitleScene::background_images[2] = { -1, -1 }; // 背景画像ハンドルの初期値は-1としておく
int TitleScene::menuX = 2000; // メニューの初期位置を画面右端に設定

TitleScene::TitleScene()
    : frameWidth(50), frameHeight(50), scaleFactor(2), lastAPressTime(0), isMenuScrolling(true)
{
    for (int i = 0; i < CHARACTER_COUNT; ++i)
    {
        currentFrames[i] = 0;
        frameCounts[i] = 0;
        for (int j = 0; j < 5; ++j)
        {
            characterImages[i][j] = -1;
        }
    }

    input_time = 0;
    can_scene_change = FALSE;
    select_menu = 0;

    help_menu = 0;
    help = false;
    credit = false;
}

TitleScene::~TitleScene()
{
}

void TitleScene::Initialize()
{
    // 効果音の読み込み
    move_se = LoadSoundMem("bgm/MoveCursor.mp3");
    decision_se = LoadSoundMem("bgm/click.mp3");
    bgm = LoadSoundMem("bgm/stageselect.mp3");

    // キャラクター画像の分割読み込み
    LoadDivGraph("image/Player/Monk/walk.png", 5, 5, 1, 50, 50, characterImages[0]);
    LoadDivGraph("image/Player/Wizard/walk.png", 5, 5, 1, 50, 50, characterImages[1]);
    LoadDivGraph("image/Player/Warrior/walk.png", 5, 5, 1, 50, 50, characterImages[2]);
    LoadDivGraph("image/Player/Hero/walk.png", 5, 5, 1, 50, 50, characterImages[3]);

    // 背景画像の読み込み
    if ((background_images[0] = LoadGraph("image/Title/back_ground.png")) == -1 ||
        (background_images[1] = LoadGraph("image/Title/back_ground.png")) == -1)
    {
        throw("image/Title/back_ground\n");
    }

    // タイトルロゴの読み込み
    if ((logo_image = LoadGraph("image/Title/logo.png")) == -1)
    {
        throw("image/Title/logo.png\n");
    }

    // メニュー画像の読み込み
    if ((LoadDivGraph("image/Title/menu.png", 8, 2, 4, 450, 75, set_menu_image)) == -1)
        throw("image/Title/menu.png\n");

    int count = 0;
    for (int i = 0; i < MENU_NUM; i++)
    {
        for (int j = 0; j < 2; j++)
            menu_image[i][j] = set_menu_image[count++];
    }
}

void TitleScene::Finalize()
{
    // 背景画像の削除
    for (int i = 0; i < 2; ++i)
    {
        DeleteGraph(background_images[i]);
    }

    // メニュー画像の削除
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 2; j++)
            DeleteGraph(menu_image[i][j]);
    }

    for (int i = 0; i < 8; i++)
        DeleteGraph(set_menu_image[i]);
    DeleteGraph(logo_image);

    DeleteSoundMem(move_se);
    DeleteSoundMem(decision_se);

    StopSoundMem(bgm);
    DeleteSoundMem(bgm);


    // TalkUIの終了処理
    talkUi.Finalize();
}

SCENE_TYPE TitleScene::Update(float delta_time)
{
    Key* key;

    // 現在の時間を取得
    int currentTime = GetNowCount(); // DXライブラリの関数を使用して現在の時間をミリ秒単位で取得

    if (CheckSoundMem(bgm) != 1)
    {   //SEが流れていなかったら再生
        PlaySoundMem(bgm, DX_PLAYTYPE_LOOP, TRUE); //SE再生
    }

    // アニメーションのフレーム更新
    for (int i = 0; i < 4; ++i)
    {
        frameCounts[i]++;
        if (frameCounts[i] >= 10) // 10フレームごとにアニメーションの更新
        {
            frameCounts[i] = 0;
            currentFrames[i] = (currentFrames[i] + 1) % 4;
        }
    }

    // 背景のスクロール
    scrollX -= SCROLL_SPEED;
    if (scrollX <= -BACKGROUND_WIDTH)
    {
        scrollX = 0;
    }

    // ロゴの移動
    if (logoX > 0)
    {
        logoX -= 2;
    }

    // メニューの移動処理
    if (menuX > 640)
    {
        menuX -= 2;
    }
    else
    {
        isMenuScrolling = false; // メニューのスクロール完了
    }

    // コントローラーのAボタンでロゴとメニューをスキップ
    if (key->KeyDown(KEY_TYPE::A))
    {
        logoX = 0;
        menuX = 640;
    }


    // メニューのスクロール完了後の操作処理
    if (!isMenuScrolling)
    {
       
        // メニュー選択
        if (!credit && !help)
        {
            // Aボタンで各シーンに移行
            if (key->KeyDown(KEY_TYPE::A) && select_menu == 0 && (currentTime - lastAPressTime) > 500)
            {
                lastAPressTime = currentTime; // 「A」ボタンが押された時間を更新
                PlaySoundMem(decision_se, DX_PLAYTYPE_BACK, TRUE);
                while (CheckSoundMem(decision_se) == 1) {}
                talkUi.Initialize();
                return SCENE_TYPE::MAIN;
            }
            else if (key->KeyDown(KEY_TYPE::A) && select_menu == 1 && (currentTime - lastAPressTime) > 500)
            {
                lastAPressTime = currentTime; // 「A」ボタンが押された時間を更新
                PlaySoundMem(decision_se, DX_PLAYTYPE_BACK, TRUE);
                return SCENE_TYPE::HELPSCENE;
            }
            else if (key->KeyDown(KEY_TYPE::A) && select_menu == 2 && (currentTime - lastAPressTime) > 500)
            {
                lastAPressTime = currentTime; // 「A」ボタンが押された時間を更新
                PlaySoundMem(decision_se, DX_PLAYTYPE_BACK, TRUE);
                return SCENE_TYPE::CREDITSCENE;
            }
            else if (key->KeyDown(KEY_TYPE::A) && select_menu == 3 && (currentTime - lastAPressTime) > 500)
            {
                lastAPressTime = currentTime; // 「A」ボタンが押された時間を更新
                PlaySoundMem(decision_se, DX_PLAYTYPE_BACK, TRUE);
                DxLib_End();
            }
          
        }

        // ヘルプメニュー処理
        if (help)
        {
            if (++input_time > INPUT_ACCEPTANCE_TIME)
            {
                if (key->GetStickAngle(KEY_TYPE::L).x > 0)
                {
                    PlaySoundMem(move_se, DX_PLAYTYPE_BACK, TRUE);
                    if (++help_menu == 3) help_menu = 0;
                    input_time = 1;
                }
                else if (key->GetStickAngle(KEY_TYPE::L).x < 0)
                {
                    PlaySoundMem(move_se, DX_PLAYTYPE_BACK, TRUE);
                    if (--help_menu < 0) help_menu = 2;
                    input_time = 1;
                }
            }

            if (key->KeyDown(KEY_TYPE::A))
            {
                input_time = 1;
                help_menu = 0;
                help = false;
            }
        }
        // クレジットメニュー処理
        else if (credit)
        {
            if (key->KeyDown(KEY_TYPE::A))
            {
                credit = false;
            }
        }
        // 通常メニュー処理
        else
        {
            if (++input_time > INPUT_ACCEPTANCE_TIME)
            {
                if ((key->GetStickAngle(KEY_TYPE::L).y > 0) || (key->KeyDown(KEY_TYPE::DOWN)))
                {
                    PlaySoundMem(move_se, DX_PLAYTYPE_BACK, TRUE);
                    if (++select_menu == 4) select_menu = 0;
                    input_time = 1;
                }
                else if ((key->GetStickAngle(KEY_TYPE::L).y < 0) || (key->KeyDown(KEY_TYPE::UP)))
                {
                    PlaySoundMem(move_se, DX_PLAYTYPE_BACK, TRUE);
                    if (--select_menu < 0) select_menu = 3;
                    input_time = 1;
                }
            }
        }
    }

    return GetNowScene();
}

void TitleScene::Draw() const
{
    // 背景画像の描画
    DrawGraph(scrollX, 0, background_images[0], TRUE);
    DrawGraph(scrollX + BACKGROUND_WIDTH, 0, background_images[1], TRUE);

    // タイトルロゴの描画
    DrawGraph(logoX, 50, logo_image, TRUE);

    // メニュー画像の描画
    for (int i = 0; i < 4; i++)
    {
        bool flg = (i == select_menu);
        DrawRotaGraph(menuX, 300 + (i * 60), 1, 0, menu_image[i][flg], TRUE);
    }

    // ヘルプ画像の描画
    if (help)
    {
        DrawRotaGraph(640, 360, 1, 0, help_image[help_menu], TRUE);
        DrawRotaGraph(890, 90, 0.3, 0, num_image[0], TRUE, TRUE);
        DrawRotaGraph(970, 90, 0.3, 0, num_image[help_menu + 1], TRUE);
        DrawRotaGraph(1050, 90, 0.3, 0, num_image[0], TRUE);
    }

    // クレジット画像の描画
    if (credit)
    {
        DrawRotaGraph(640, 360, 1, 0, credit_image, TRUE);
    }

    // キャラクター画像の描画
    int startX = 420;
    int startY = 575;
    int spacing = 100;

    for (int i = 0; i < 4; ++i)
    {
        if (characterImages[i][currentFrames[i]] != -1)
        {
            int x = startX + i * spacing;
            int y = startY;

            int scaledWidth = frameWidth * scaleFactor;
            int scaledHeight = frameHeight * scaleFactor;
            DrawExtendGraph(x, y, x + scaledWidth, y + scaledHeight, characterImages[i][currentFrames[i]], TRUE);
        }
    }
}

SCENE_TYPE TitleScene::GetNowScene() const
{
    return SCENE_TYPE::TITLE;
}
