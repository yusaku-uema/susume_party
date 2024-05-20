#include "GameOverScene.h"
#include "Key.h"
#include "DxLib.h"
#include <fstream>
#include <codecvt>  // for codecvt_utf8
#include <locale>   // for wstring_convert
#include <iostream>

#define  FONT_SIZE 48

GameOverScene::GameOverScene() {
	// ゲームオーバー画像の読み込み
	if ((gameover_image = LoadGraph("image/GameOver/gameover.png")) == -1)
		throw("ゲームオーバー画像読込み失敗\n");

	transparency = 0;
	transparencySpeed = 1;
	imagePosX = 350;
	imagePosY = 0;
}


void GameOverScene::LoadText() {
	textLoaded = true;
	FileHandle = FileRead_open("txt/2st.txt");

	while (FileRead_eof(FileHandle) == 0) {
		char text[256];
		if (FileRead_gets(text, sizeof(text), FileHandle) != -1) {
			std::string line(text);
			// 改行文字を削除
			if (!line.empty() && (line.back() == '\n' || line.back() == '\r')) {
				line.pop_back();
			}
			textLines.push_back(line);
		}
	}

	FileRead_close(FileHandle);
}


GameOverScene::~GameOverScene() {
	if (FileHandle != 0) {
		FileRead_close(FileHandle);
	}
}


void GameOverScene::Initialize() 
{
	SetFontSize(FONT_SIZE);
}


void GameOverScene::Finalize() {}


SCENE_TYPE GameOverScene::Update(float delta_time) {

	if (Key::KeyDown(KEY_TYPE::A))return SCENE_TYPE::TITLE;

	frameCount++;  // フレームカウントを更新

	if (transparency < 255) {
		transparency += transparencySpeed;
	}
	else {
		// 透明度が255に達してからの時間を更新
		if (transparency == 255 && !textLoaded) {
			timeSinceFullTransparency += delta_time;
			if (timeSinceFullTransparency >= 1.0) { // 3秒後にテキストを読み込む
				LoadText();
				textLoaded = true;
				frameCount = 0;  // フレームカウントをリセット
			}
		}
	}

	return GetNowScene();
}


void GameOverScene::Draw() const {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, transparency);
	DrawGraph(imagePosX, imagePosY, gameover_image, TRUE);

	if (textLoaded) {
		int y = 400;
		int totalCharCount = frameCount / 15; // 15フレームごとに1文字ずつ表示
		int charCounter = 0;

		for (const auto& line : textLines) {
			int lineCharCount = line.length();
			if (charCounter + lineCharCount <= totalCharCount) {
				// この行全体を表示する
				talk(430, y, line.c_str(), lineCharCount);
			}
			else {
				// 部分的に表示する
				talk(430, y, line.c_str(), totalCharCount - charCounter);
				break; // これ以上表示する文字がないのでループを抜ける
			}
			charCounter += lineCharCount; // この行の文字数をカウンターに追加
			y += FONT_SIZE;
		}
	}

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

//1文字ずつ文字を表示　全角半角対応
void GameOverScene::talk(int x, int y, const char* t, int availableChars) const {

	////フォント替える時に使う　今は使わない
    int fontHandle = CreateFontToHandle("dotfont", 15, -2);
   ChangeFont("dotfont"); // フォントを設定

	int color = GetColor(255, 255, 255);//色	
	int length = strlen(t); // 文字列の長さを取得

	for (int i = 0; i < availableChars && i < length; i++) {
		int Size = GetCharBytes(DX_CHARCODEFORMAT_SHIFTJIS, t + i);
		if (t[i] == '\n') { // 改行文字を検出
			y += FONT_SIZE; // y座標を更新して改行
			x = 100; // x座標をリセット
		}
		else if (Size == 1) { // 半角文字
			DrawFormatString(x, y, color, "%c", t[i]);
			x += FONT_SIZE/2; // 次の文字のためのX座標を更新
		}
		else { // 全角文字
			DrawFormatString(x, y, color, "%c%c", t[i], t[i + 1]);
			x += FONT_SIZE; // 全角文字のためのX座標を更新
			i++; // 全角文字は2バイトなのでインデックスを1つ追加でスキップ
		}
	}
}

SCENE_TYPE GameOverScene::GetNowScene() const {
	return SCENE_TYPE::GAME_OVER;
}
