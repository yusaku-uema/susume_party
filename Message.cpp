#include "Message.h"
#include "Key.h"
#include "DxLib.h"

#define FONT_SIZE 35//文字の大きさ
#define DRAW_TEXT_TIME 0.2f//1文字表示するまでの時間

#define DRAW_TEXT_LOCATION_X 50
#define DRAW_TEXT_LOCATION_Y 550

Message::Message(const char* text_data_name) : draw_text_time(0.0f), draw_text_count(0)
{
	SetFontSize(FONT_SIZE);

	int text_data = NULL;
	if ((text_data = FileRead_open(text_data_name)) == 0)throw("text_dataが読み込めません\n");

	while (FileRead_eof(text_data) == 0)
	{
		char text[256];

		if (FileRead_gets(text, sizeof(text), text_data) != -1)
		{
			text_line.push_back(text);
			text_line.back() += "\n";
		}
		else break;
	}
	FileRead_close(text_data);

	//フォント作成
	//font = CreateFontToHandle("dotfont", FONT_SIZE, -1);
}

Message::~Message()
{
	text_line.clear();
	text_line.shrink_to_fit();

	DeleteFontToHandle(font);
}

bool Message::Update(float delta_time)
{
	//一定時間経過で、表示文字を増やす
	if ((draw_text_time += delta_time) > DRAW_TEXT_TIME)
	{
		draw_text_count++;
		draw_text_time = 0.0f;
	}

	return false;
}

void Message::Draw() const
{
	DrawBox(0, 540, 1280, 720, 0x000000, TRUE);
	DrawBox(0, 540, 1280, 720, 0xffffff, FALSE);

	//現在表示できる文字数
	int draw_text_count = this->draw_text_count;

	//文字の表示位置
	DATA text_location = { DRAW_TEXT_LOCATION_X, DRAW_TEXT_LOCATION_Y };

	//コメントを1行ずつループする
	for (int i = 0; i < text_line.size(); i++)
	{
		//現在の行の文字数繰り返す
		for (int j = 0; j < text_line[i].length(); j++)
		{
			//文字のサイズを調べる
			int text_size = GetCharBytes(DX_CHARCODEFORMAT_SHIFTJIS, text_line[i].c_str() + j);

			//表示できる文字が足りない場合、抜ける
			if (draw_text_count <= 0)break;

			else if (*(text_line[i].c_str() + j) == '\n')
			{
				//改行文字の場合
				text_location.y += FONT_SIZE + 5; // y座標を更新して改行
				text_location.x = DRAW_TEXT_LOCATION_X; // x座標をリセット
			}
			else if (text_size == 1)
			{
				//半角文字の場合
				DrawFormatString(text_location.x, text_location.y, 0xffffff, "%c", *(text_line[i].c_str() + j));
				text_location.x += (FONT_SIZE / 2); // X座標を更新
				draw_text_count--;
			}
			else
			{
				// 全角文字の場合
				DrawFormatString(text_location.x, text_location.y, 0xffffff, "%c%c", *(text_line[i].c_str() + j), *(text_line[i].c_str() + j + 1));
				text_location.x += FONT_SIZE; //X座標を更新
				draw_text_count--;
				j++; // 全角文字は2バイトなのでインデックスを1つ追加でスキップ
			}
		}
	 }
}