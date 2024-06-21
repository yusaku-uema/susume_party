#include "GameOverScene.h"
#include "DxLib.h"

GameOverScene::GameOverScene() : alpha(0), alpha_speed(2), message(nullptr), option_selected(false), message_displayed(false)
{
    // ゲームオーバー文字画像
    if ((gameover_image = LoadGraph("image/GameOver/gameover.png")) == -1)
        throw("image/GameOver/gameover.pngが読み込めません\n");

    // メッセージ作成
    message = new Message("txt/gameover.txt");

    bgm= LoadSoundMem("bgm/gameover.mp3");

    // 選択肢画像の読み込み
    option_yes_image = LoadGraph("image/GameOver/yes.png");
    option_no_image = LoadGraph("image/GameOver/no.png");

    if (option_yes_image == -1 || option_no_image == -1)
        throw("yes.pngとno.pngが読み込まれませんでした\n");
}

GameOverScene::~GameOverScene()
{
    // 画像の削除
    DeleteGraph(gameover_image);
    DeleteGraph(option_yes_image);
    DeleteGraph(option_no_image);
    delete message; // メッセージの削除

    StopSoundMem(bgm);
    DeleteSoundMem(bgm);

}

void GameOverScene::Initialize()
{
    alpha = 0; // 初期化時に透明度をリセット
    message_displayed = false; // メッセージ表示フラグをリセット
}

void GameOverScene::Finalize()
{
}

SCENE_TYPE GameOverScene::Update(float delta_time)
{


    if (CheckSoundMem(bgm) != 1)
    {   //SEが流れていなかったら再生
        PlaySoundMem(bgm, DX_PLAYTYPE_LOOP, TRUE); //SE再生
    }


    // 透明度の増加
    if (alpha < 255)
    {
        alpha += alpha_speed; // フェードの速度
        if (alpha > 255) alpha = 255; // 最大値を超えないように
    }
    else
    {
        // メッセージの更新
        if (!message_displayed && message->Update(delta_time))
        {
            // メッセージがすべて表示された後の処理
            message_displayed = true; // メッセージ表示フラグを設定
        }

        if (message_displayed) {
            // 十字キーの入力状態を取得
            int pad_input = GetJoypadInputState(DX_INPUT_PAD1);

            // 左スティックの入力
            int l_stick_x, l_stick_y;
            GetJoypadAnalogInput(&l_stick_x, &l_stick_y, DX_INPUT_PAD1);

            // スティックの左入力処理
            if (l_stick_x < -8000 || (pad_input & PAD_INPUT_LEFT))
            {
                option_selected = true; // 「はい」を選択
            }
            // スティックの右入力処理
            else if (l_stick_x > 8000 || (pad_input & PAD_INPUT_RIGHT))
            {
                option_selected = false; // 「いいえ」を選択
            }

            // 選択決定の処理
            if (pad_input & PAD_INPUT_B) // Aボタン（XboxコントローラーのAボタン）
            {
                if (option_selected)
                {
                    // 「はい」を選択した場合の処理
                    // 次のシーンへ遷移する処理をここに追加
                    return SCENE_TYPE::TITLE;
                   
                }
                else
                {
                    // 「いいえ」を選択した場合の処理
                    // ゲームオーバーに戻る処理をここに追加
                    return SCENE_TYPE::MAIN;
                   
                }
            }
        }
    }
    return GetNowScene();
}

void GameOverScene::Draw() const
{
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha); // アルファブレンドモードに設定して描画
    DrawGraph(325, 50, gameover_image, TRUE); // ゲームオーバー文字の表示
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); // ブレンドモードを元に戻す

    // メッセージ表示
    if (alpha == 255) {
        message->Draw();

        // メッセージが表示され終わった後に「いいえ」の画像を表示
        if (message_displayed) {
          

            // 選択肢の表示
            if (option_selected)
            {
                //DrawString(0, 40, "デバック: はい", 0xffffff);
                DrawGraph(200, 0, option_yes_image, TRUE);
            }
            else
            {
                //DrawString(0, 60, "デバック: いいえ", 0xffffff);
                DrawGraph(200, 0, option_no_image, TRUE);
            }
        }
    }
    
}

SCENE_TYPE GameOverScene::GetNowScene() const
{
    return SCENE_TYPE::GAME_OVER;
}
