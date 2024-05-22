//#include "GameOverScene.h"
//#include "Key.h"
//#include "DxLib.h"
//#include <fstream>
//#include <codecvt>  // for codecvt_utf8
//#include <locale>   // for wstring_convert
//#include <iostream>
//
//#define  FONT_SIZE 48
//#define  ADD_IMAGE_TRANSPARENCY //1�t���[���ɉ��Z�����摜�̓��ߓx
//
//GameOverScene::GameOverScene() : frame_count(0), image_location(DATA{ 350.0f, 0.0f }), draw_text(false)
//{
//	// �Q�[���I�[�o�[�摜�̓ǂݍ���
//	if ((gameover_image = LoadGraph("image/GameOver/gameover.png")) == -1)throw("�Q�[���I�[�o�[�摜�Ǎ��ݎ��s\n");
//
//	//�e�L�X�g�̓ǂݍ���
//	LoadText();
//}
//
//
//void GameOverScene::LoadText()
//{
//	int file_handle = FileRead_open("txt/2st.txt");
//
//	//txt�̕�����ǂݍ���
//	while (FileRead_eof(file_handle) == 0)
//	{
//		char text[256];
//
//		//������1�s����text�ɓ����
//		if (FileRead_gets(text, sizeof(text), file_handle) != -1)
//		{
//			//text�̕�����string�^��line�ɓ����
//			std::string line(text);
//
//			//line���󂶂�Ȃ��A���������s�����̏ꍇ
//			if (!line.empty() && (line.back() == '\n' || line.back() == '\r'))
//			{
//				//����������
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
//	//500�t���[���ȏソ�����ꍇ�e�L�X�g��\��
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
//		int total_char_count = frame_count / 15; // 15�t���[�����Ƃ�1�������\��
//		int char_counter = 0;
//
//		//��s�����[�v����
//		for (int i = 0; i < text_line.size(); i++)
//		{
//			//���̍s�̕��������J�E���g
//			int line_char_count = text_line[i].length();
//
//			if (char_counter + line_char_count <= total_char_count)
//			{
//				// ���̍s�S�̂�\������
//				talk(430, 400, line.c_str(), lineCharCount);
//			}
//			else
//			{
//				// �����I�ɕ\������
//				talk(430, y, line.c_str(), totalCharCount - charCounter);
//				break; // ����ȏ�\�����镶�����Ȃ��̂Ń��[�v�𔲂���
//			}
//
//			charCounter += lineCharCount; // ���̍s�̕��������J�E���^�[�ɒǉ�
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
//				// ���̍s�S�̂�\������
//				talk(430, 400, line.c_str(), lineCharCount);
//			}
//			else
//			{
//				// �����I�ɕ\������
//				talk(430, y, line.c_str(), totalCharCount - charCounter);
//				break; // ����ȏ�\�����镶�����Ȃ��̂Ń��[�v�𔲂���
//			}
//
//			charCounter += lineCharCount; // ���̍s�̕��������J�E���^�[�ɒǉ�
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
////1������������\���@�S�p���p�Ή�
//void GameOverScene::talk(int x, int y, const char* t, int availableChars) const
//{
//
//	////�t�H���g�ւ��鎞�Ɏg���@���͎g��Ȃ�
//    int fontHandle = CreateFontToHandle("dotfont", 15, -2);
//   ChangeFont("dotfont"); // �t�H���g��ݒ�
//
//	int color = GetColor(255, 255, 255);//�F	
//	int length = strlen(t); // ������̒������擾
//
//	for (int i = 0; i < availableChars && i < length; i++)
//	{
//		int Size = GetCharBytes(DX_CHARCODEFORMAT_SHIFTJIS, t + i);
//
//		if (t[i] == '\n') 
//		{ // ���s���������o
//			y += FONT_SIZE; // y���W���X�V���ĉ��s
//			x = 100; // x���W�����Z�b�g
//		}
//		else if (Size == 1)
//		{ // ���p����
//			DrawFormatString(x, y, color, "%c", t[i]);
//			x += FONT_SIZE/2; // ���̕����̂��߂�X���W���X�V
//		}
//		else
//		{// �S�p����
//			DrawFormatString(x, y, color, "%c%c", t[i], t[i + 1]);
//			x += FONT_SIZE; // �S�p�����̂��߂�X���W���X�V
//			i++; // �S�p������2�o�C�g�Ȃ̂ŃC���f�b�N�X��1�ǉ��ŃX�L�b�v
//		}
//	}
//}
//
//SCENE_TYPE GameOverScene::GetNowScene() const
//{
//	return SCENE_TYPE::GAME_OVER;
//}
