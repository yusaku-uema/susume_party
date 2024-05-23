#include "Message.h"
#include "Key.h"
#include "DxLib.h"

#define FONT_SIZE 35//文字の大きさ
#define DRAW_TEXT_TIME 0.05f//1文字表示するまでの時間

#define DRAW_TEXT_LOCATION_X 50.0f
#define DRAW_TEXT_LOCATION_Y 550.0f

#define MAX_DRAW_TEXT_LINE 3//1度に表示できるメッセージの行数(最大)
#define MAX_DRAW_TEXT_NUM 300//1度に表示できる文字数

Message::Message(const char* text_data_name) : draw_text_time(0.0f), draw_line_text_num(0),
update_text_line(0), update_line_text_num(0), draw_start_text_line(0), can_update_text_line(true)
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

	//1行目の文字の数を数える
	update_line_text_num = GetLineTextNum(update_text_line);

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
	//表示できる文字を越えた場合
	if (update_line_text_num == -1)
	{
		//Aボタンを入力で終了
		if (Key::KeyDown(KEY_TYPE::A))return true;
	}
	else if (!can_update_text_line)
	{
		if (Key::KeyDown(KEY_TYPE::A))
		{
			can_update_text_line = true;
			UpdateTextLine();
		}
	}
	else if ((draw_text_time += delta_time) > DRAW_TEXT_TIME)
	{
		if (++draw_line_text_num > update_line_text_num)
		{
			if ((update_text_line + 1) % MAX_DRAW_TEXT_LINE == 0)can_update_text_line = false;
			else UpdateTextLine();
		}
		draw_text_time = 0.0f;
	}

	return false;
}

void Message::UpdateTextLine()
{
	if ((update_line_text_num = GetLineTextNum(++update_text_line)) == -1)
	{
		update_text_line--;
		draw_line_text_num--;
	}
	else draw_line_text_num = 0;

	draw_start_text_line = update_text_line - (MAX_DRAW_TEXT_LINE - 1);
	if (draw_start_text_line < 0)draw_start_text_line = 0;
}

int Message::GetLineTextNum(int draw_text_line)const
{
	//文字数をカウントする変数
	int text_count = 0;

	if (draw_text_line < text_line.size())
	{
		for (int i = 0; i < text_line[draw_text_line].length(); i++)
		{
			//文字のサイズを調べる
			int text_size = GetCharBytes(DX_CHARCODEFORMAT_SHIFTJIS, text_line[draw_text_line].c_str() + i);

			if (*(text_line[draw_text_line].c_str() + i) == '\n')
			{
				break;
			}
			else if (text_size == 1)
			{
				text_count++;
			}
			else if (text_size == 2)
			{
				text_count++;
				i++;
			}
		}
	}
	else return - 1;

	//文字数を返す
	return text_count;
}

void Message::Draw() const
{
	DrawBox(0, 540, 1280, 720, 0x000000, TRUE);
	DrawBox(0, 540, 1280, 720, 0xffffff, FALSE);

	//現在表示できる文字数
	int draw_line_text_num = this->draw_line_text_num;

	//文字の表示位置
	DATA text_location = { DRAW_TEXT_LOCATION_X, DRAW_TEXT_LOCATION_Y };

	for (int i = draw_start_text_line; i < text_line.size(); i++)
	{
		if (i > update_text_line)break;

		for (int j = 0; j < text_line[i].length(); j++)
		{
			//文字のサイズを調べる
			int text_size = GetCharBytes(DX_CHARCODEFORMAT_SHIFTJIS, text_line[i].c_str() + j);

			if (i == update_text_line)
			{
				if (draw_line_text_num <= 0)break;
			}

			if (*(text_line[i].c_str() + j) == '\n')
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
				if(i == update_text_line)draw_line_text_num--;
			}
			else  if (text_size == 2)
			{
				// 全角文字の場合
				DrawFormatString(text_location.x, text_location.y, 0xffffff, "%c%c", *(text_line[i].c_str() + j), *(text_line[i].c_str() + j + 1));
				text_location.x += FONT_SIZE; //X座標を更新
				if (i == update_text_line)draw_line_text_num--;
				j++;
			}
		}
	}

	DrawFormatString(100, 100,0xffffff, "%f", draw_text_time);
}