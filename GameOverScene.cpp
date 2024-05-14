#include "GameOverScene.h"
#include "Key.h"
#include "DxLib.h"
#include <fstream>
#include <codecvt>  // for codecvt_utf8
#include <locale>   // for wstring_convert

GameOverScene::GameOverScene() {
    // ゲームオーバー画像の読み込み
    if ((gameover_image = LoadGraph("image/GameOver/gameover.png")) == -1)
        throw("ゲームオーバー画像読込み失敗\n");

    transparency = 0;
    transparencySpeed = 1;
    imagePosX = 350;
    imagePosY = 0;
}

GameOverScene::~GameOverScene() {
    if (FileHandle != 0) {
        FileRead_close(FileHandle);
    }
}

// 初期化処理
void GameOverScene::Initialize() {}

// 終了時処理
void GameOverScene::Finalize() {}

// 更新処理
SCENE_TYPE GameOverScene::Update(float delta_time) {
    frameCount++;  // フレームカウントを更新

    if (transparency < 255) {
        transparency += transparencySpeed;
    }
    else if (transparency == 255 && !textLoaded) {
        textLoaded = true;
        LoadText();
    }

    return GetNowScene();
}

// 描画処理
void GameOverScene::Draw() const {
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, transparency);
    DrawGraph(imagePosX, imagePosY, gameover_image, TRUE);

    if (transparency == 255) {
        int y = 300;
        for (const auto& line : textLines) {
            talk(100, y, line.c_str(), frameCount);  // `talk`を使用してテキストを描画
            y += 20;
        }
    }

    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void GameOverScene::talk(int x, int y, const char* t, int frameCount) const {
    int color = GetColor(255, 255, 255);
    int length = strlen(t); // 文字列の長さを取得
    int charCount = frameCount / 15; // 15フレームごとに1文字ずつ表示

    for (int i = 0; i < charCount && t[i] != '\0'; i++) {
        int Size = GetCharBytes(DX_CHARCODEFORMAT_SHIFTJIS, t + i);
        if (Size == 1) { // 半角文字
            DrawFormatString(x, y, color, "%c", t[i]);
            x += 9; // 次の文字のためのX座標を更新
        }
        else { // 全角文字
            DrawFormatString(x, y, color, "%c%c", t[i], t[i + 1]);
            x += 17; // 全角文字のためのX座標を更新
            i++; // 全角文字は2バイトなのでインデックスを1つ追加でスキップ
        }
    }
}

void GameOverScene::LoadText() {
    textLoaded = true;
    FileHandle = FileRead_open("txt/1st.txt");

    while (FileRead_eof(FileHandle) == 0) {
        FileRead_gets(text, sizeof(text), FileHandle);
        textLines.push_back(std::string(text)); // Convert to string to store in vector
    }

    FileRead_close(FileHandle);
}

// 現在のシーン情報を取得
SCENE_TYPE GameOverScene::GetNowScene() const {
    return SCENE_TYPE::GAME_OVER;
}
