//#include "GameOverScene.h"
//#include "Key.h"
//#include "DxLib.h"
//#include <fstream>
//#include <codecvt>  // for codecvt_utf8
//#include <locale>   // for wstring_convert
//#include <iostream>
//
//#define  FONT_SIZE 48
//#define  ADD_IMAGE_TRANSPARENCY //1フレームに加算される画像の透過度
//
//GameOverScene::GameOverScene() : frame_count(0), image_location(DATA{ 350.0f, 0.0f }), draw_text(false)
//{
//	// ゲームオーバー画像の読み込み
//	if ((gameover_image = LoadGraph("image/GameOver/gameover.png")) == -1)throw("ゲームオーバー画像読込み失敗\n");
//
//	//テキストの読み込み
//	LoadText();
//}
//
//
//void GameOverScene::LoadText()
//{
//	int file_handle = FileRead_open("txt/2st.txt");
//
//	//txtの文字を読み込む
//	while (FileRead_eof(file_handle) == 0)
//	{
//		char text[256];
//
//		//文字を1行ずつtextに入れる
//		if (FileRead_gets(text, sizeof(text), file_handle) != -1)
//		{
//			//textの文字をstring型のlineに入れる
//			std::string line(text);
//
//			//lineが空じゃなく、末尾が改行文字の場合
//			if (!line.empty() && (line.back() == '\n' || line.back() == '\r'))
//			{
//				//末尾を消す
//				line.pop_back();
//			}
//
//			text_line.push_back(line);
//		}
//	}
//
//	FileRead_close(file_handle);
//}
//
//
//GameOverScene::~GameOverScene()
//{
//}
//
//
//void GameOverScene::Initialize() 
//{
//	SetFontSize(FONT_SIZE);
//}
//
//
//void GameOverScene::Finalize() {}
//
//
//SCENE_TYPE GameOverScene::Update(float delta_time)
//{
//	if (Key::KeyDown(KEY_TYPE::A))return SCENE_TYPE::TITLE;
//
//	//500フレーム以上たった場合テキストを表示
//
//	frame_count++;
//
//	if (draw_text)
//	{
//		
//	}
//	else if (frame_count > 500)
//	{
//		draw_text = true;
//		frame_count = 0;
//	}
//
//	return GetNowScene();
//}
//
//void GameOverScene::Draw() const
//{
//	int image_transparency = frame_count;
//
//	if (draw_text)
//	{
//		image_transparency = 255;
//
//		int total_char_count = frame_count / 15; // 15フレームごとに1文字ずつ表示
//		int char_counter = 0;
//
//		//一行ずつループする
//		for (int i = 0; i < text_line.size(); i++)
//		{
//			//この行の文字数をカウント
//			int line_char_count = text_line[i].length();
//
//			if (char_counter + line_char_count <= total_char_count)
//			{
//				// この行全体を表示する
//				talk(430, 400, line.c_str(), lineCharCount);
//			}
//			else
//			{
//				// 部分的に表示する
//				talk(430, y, line.c_str(), totalCharCount - charCounter);
//				break; // これ以上表示する文字がないのでループを抜ける
//			}
//
//			charCounter += lineCharCount; // この行の文字数をカウンターに追加
//			y += FONT_SIZE;
//		}
//
//
//
//
//
//
//		for (const auto& line : text_line)
//		{
//			int lineCharCount = line.length();
//			if (charCounter + lineCharCount <= totalCharCount)
//			{
//				// この行全体を表示する
//				talk(430, 400, line.c_str(), lineCharCount);
//			}
//			else
//			{
//				// 部分的に表示する
//				talk(430, y, line.c_str(), totalCharCount - charCounter);
//				break; // これ以上表示する文字がないのでループを抜ける
//			}
//
//			charCounter += lineCharCount; // この行の文字数をカウンターに追加
//			y += FONT_SIZE;
//		}
//	}
//	else if (image_transparency > 255)image_transparency = 255;
//	
//	SetDrawBlendMode(DX_BLENDMODE_ALPHA, image_transparency);
//	DrawGraph(image_location.x, image_location.y, gameover_image, TRUE);
//
//	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
//}
//
////1文字ずつ文字を表示　全角半角対応
//void GameOverScene::talk(int x, int y, const char* t, int availableChars) const
//{
//
//	////フォント替える時に使う　今は使わない
//    int fontHandle = CreateFontToHandle("dotfont", 15, -2);
//   ChangeFont("dotfont"); // フォントを設定
//
//	int color = GetColor(255, 255, 255);//色	
//	int length = strlen(t); // 文字列の長さを取得
//
//	for (int i = 0; i < availableChars && i < length; i++)
//	{
//		int Size = GetCharBytes(DX_CHARCODEFORMAT_SHIFTJIS, t + i);
//
//		if (t[i] == '\n') 
//		{ // 改行文字を検出
//			y += FONT_SIZE; // y座標を更新して改行
//			x = 100; // x座標をリセット
//		}
//		else if (Size == 1)
//		{ // 半角文字
//			DrawFormatString(x, y, color, "%c", t[i]);
//			x += FONT_SIZE/2; // 次の文字のためのX座標を更新
//		}
//		else
//		{// 全角文字
//			DrawFormatString(x, y, color, "%c%c", t[i], t[i + 1]);
//			x += FONT_SIZE; // 全角文字のためのX座標を更新
//			i++; // 全角文字は2バイトなのでインデックスを1つ追加でスキップ
//		}
//	}
//}
//
//SCENE_TYPE GameOverScene::GetNowScene() const
//{
//	return SCENE_TYPE::GAME_OVER;
//}
