#include "GameOverScene.h"
#include "Key.h"
#include "DxLib.h"
#include <fstream>


GameOverScene::GameOverScene() {
    // ゲームオーバー画像の読み込み
    if ((gameover_image = LoadGraph("image/GameOver/gameover.png")) == -1)
        throw("ゲームオーバー画像読込み失敗\n");

    transparency = 0;
    transparencySpeed = 1;
    imagePosX = 350;
    imagePosY = 0;

}


GameOverScene::~GameOverScene() {}

// 初期化処理
void GameOverScene::Initialize() {}

// 終了時処理
void GameOverScene::Finalize() {}

// 更新処理
SCENE_TYPE GameOverScene::Update(float delta_time) {
    if (transparency < 255) {
        transparency += transparencySpeed;
    }
    if (transparency == 255 && textIndex < textLength) {
        textIndex++;  // テキストを一文字ずつ増やす
    }

    return GetNowScene();
}

// 描画処理
void GameOverScene::Draw() const {
    // 透明度設定
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, transparency);

    // 画像描画
    DrawGraph(imagePosX, imagePosY, gameover_image, TRUE);


    // 透明度を元に戻す
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

// 現在のシーン情報を取得
SCENE_TYPE GameOverScene::GetNowScene() const {
    return SCENE_TYPE::GAME_OVER;
}
