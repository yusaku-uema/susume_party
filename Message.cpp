#include "Message.h"
#include "Key.h"
#include "DxLib.h"

#define FONT_SIZE 35//�����̑傫��
#define DRAW_TEXT_TIME 0.2f//1�����\������܂ł̎���

#define DRAW_TEXT_LOCATION_X 50
#define DRAW_TEXT_LOCATION_Y 550

Message::Message(const char* text_data_name) : draw_text_time(0.0f), draw_text_count(0)
{
	SetFontSize(FONT_SIZE);

	int text_data = NULL;
	if ((text_data = FileRead_open(text_data_name)) == 0)throw("text_data���ǂݍ��߂܂���\n");

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

	//�t�H���g�쐬
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
	//��莞�Ԍo�߂ŁA�\�������𑝂₷
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

	//���ݕ\���ł��镶����
	int draw_text_count = this->draw_text_count;

	//�����̕\���ʒu
	DATA text_location = { DRAW_TEXT_LOCATION_X, DRAW_TEXT_LOCATION_Y };

	//�R�����g��1�s�����[�v����
	for (int i = 0; i < text_line.size(); i++)
	{
		//���݂̍s�̕������J��Ԃ�
		for (int j = 0; j < text_line[i].length(); j++)
		{
			//�����̃T�C�Y�𒲂ׂ�
			int text_size = GetCharBytes(DX_CHARCODEFORMAT_SHIFTJIS, text_line[i].c_str() + j);

			//�\���ł��镶��������Ȃ��ꍇ�A������
			if (draw_text_count <= 0)break;

			else if (*(text_line[i].c_str() + j) == '\n')
			{
				//���s�����̏ꍇ
				text_location.y += FONT_SIZE + 5; // y���W���X�V���ĉ��s
				text_location.x = DRAW_TEXT_LOCATION_X; // x���W�����Z�b�g
			}
			else if (text_size == 1)
			{
				//���p�����̏ꍇ
				DrawFormatString(text_location.x, text_location.y, 0xffffff, "%c", *(text_line[i].c_str() + j));
				text_location.x += (FONT_SIZE / 2); // X���W���X�V
				draw_text_count--;
			}
			else
			{
				// �S�p�����̏ꍇ
				DrawFormatString(text_location.x, text_location.y, 0xffffff, "%c%c", *(text_line[i].c_str() + j), *(text_line[i].c_str() + j + 1));
				text_location.x += FONT_SIZE; //X���W���X�V
				draw_text_count--;
				j++; // �S�p������2�o�C�g�Ȃ̂ŃC���f�b�N�X��1�ǉ��ŃX�L�b�v
			}
		}
	 }
}