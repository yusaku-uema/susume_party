#include "GameOverScene.h"
#include "Key.h"
#include "DxLib.h"

GameOverScene::GameOverScene() {
    FileHandle = 0;
    memset(text, 0, sizeof(text));
}

GameOverScene::~GameOverScene() {}

//初期化処理
void GameOverScene::Initialize() {}

//終了時処理
void GameOverScene::Finalize() {}

//更新処理
SCENE_TYPE GameOverScene::Update(float delta_time) {
    if (Key::KeyDown(KEY_TYPE::A)) return SCENE_TYPE::MAIN;

    // file.txtを開く
    FileHandle = FileRead_open("file.txt");

    while (FileRead_eof(FileHandle) == 0) {
        FileRead_gets(text, sizeof(text), FileHandle);
        flag = false;
        count = 0;
        while (!flag) {
            talk(draw_x, draw_y, text, count);
            ScreenFlip();
            ProcessMessage();
            ++count;
            if (ProcessMessage() != 0) break; // キーが押されたらループを抜ける
        }
        if (ProcessMessage() != 0) break; // キーが押されたらループを抜ける
        draw_y += 20;
    }

    // キー入力待ち
    while (!ProcessMessage()) {
        if (CheckHitKey(KEY_INPUT_A)) {
            break;
        }
    }

    // ファイルを閉じる
    FileRead_close(FileHandle);

    // 同様の処理をfile2.txtに対して行う
    ClearDrawScreen();

    draw_x = 0;
    draw_y = 0;
    FileHandle = FileRead_open("file2.txt");

    while (FileRead_eof(FileHandle) == 0) {
        FileRead_gets(text, sizeof(text), FileHandle);
        flag = false;
        count = 0;
        while (!flag) {
            talk(draw_x, draw_y, text, count);
            ScreenFlip();
            ProcessMessage();
            ++count;
            if (ProcessMessage() != 0) break; // キーが押されたらループを抜ける
        }
        if (ProcessMessage() != 0) break; // キーが押されたらループを抜ける
        draw_y += 20;
    }

    // キー入力待ち
    while (!ProcessMessage()) {
        if (CheckHitKey(KEY_INPUT_A)) {
            break;
        }
    }

    // ファイルを閉じる
    FileRead_close(FileHandle);

    // 同様の処理をfile3.txtに対して行う
    ClearDrawScreen();
    draw_x = 0;
    draw_y = 0;
    FileHandle = FileRead_open("file3.txt");

    while (FileRead_eof(FileHandle) == 0) {
        FileRead_gets(text, sizeof(text), FileHandle);
        flag = false;
        count = 0;
        while (!flag) {
            talk(draw_x, draw_y, text, count);
            ScreenFlip();
            ProcessMessage();
            ++count;
            if (ProcessMessage() != 0) break; // キーが押されたらループを抜ける
        }
        if (ProcessMessage() != 0) break; // キーが押されたらループを抜ける
        draw_y += 20;
    }

    // キー入力待ち
    while (!ProcessMessage()) {
        if (CheckHitKey(KEY_INPUT_A)) {
            break;
        }
    }

    // ファイルを閉じる
    FileRead_close(FileHandle);

    return GetNowScene();
}

//描画処理
void GameOverScene::Draw() const 
{


}

void GameOverScene::talk(int x, int y, const char t[], int nCount) {
    int n = nCount / 15;

    int fontHandle = CreateFontToHandle("dotfont", 15, -1);
    ChangeFont("dotfont"); //フォントを設定

    unsigned int color = GetColor(255, 255, 255);
    for (int i = 0; i < n + 1; i++) {
        if (t[i] == '\0') {
            flag = true;
            break;
        }

        int Size = GetCharBytes(DX_CHARCODEFORMAT_SHIFTJIS, t + i);

        if (Size == 1) {
            DrawFormatStringToHandle(x, y, color, fontHandle, "%c", t[i]);
            x += 9;
        }
        else {
            DrawFormatStringToHandle(x, y, color, fontHandle, "%c%c", t[i], t[i + 1]);
            x += 17;
            i++;
            n++;
        }
        if (x > 790) {
            x = 10;
            y += 20;
        }
    }

    //フォントハンドルを削除
    DeleteFontToHandle(fontHandle);
}

//現在のシーン情報を取得
SCENE_TYPE GameOverScene::GetNowScene() const {
    return SCENE_TYPE::GAME_OVER;
}
