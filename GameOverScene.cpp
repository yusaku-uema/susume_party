#include "GameOverScene.h"
#include "Key.h"
#include "DxLib.h"
#include <fstream>
#include <codecvt>  // for codecvt_utf8
#include <locale>   // for wstring_convert
#include <iostream>

#define  FONT_SIZE 48

GameOverScene::GameOverScene() {
	// �Q�[���I�[�o�[�摜�̓ǂݍ���
	if ((gameover_image = LoadGraph("image/GameOver/gameover.png")) == -1)
		throw("�Q�[���I�[�o�[�摜�Ǎ��ݎ��s\n");

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
			// ���s�������폜
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

	frameCount++;  // �t���[���J�E���g���X�V

	if (transparency < 255) {
		transparency += transparencySpeed;
	}
	else {
		// �����x��255�ɒB���Ă���̎��Ԃ��X�V
		if (transparency == 255 && !textLoaded) {
			timeSinceFullTransparency += delta_time;
			if (timeSinceFullTransparency >= 1.0) { // 3�b��Ƀe�L�X�g��ǂݍ���
				LoadText();
				textLoaded = true;
				frameCount = 0;  // �t���[���J�E���g�����Z�b�g
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
		int totalCharCount = frameCount / 15; // 15�t���[�����Ƃ�1�������\��
		int charCounter = 0;

		for (const auto& line : textLines) {
			int lineCharCount = line.length();
			if (charCounter + lineCharCount <= totalCharCount) {
				// ���̍s�S�̂�\������
				talk(430, y, line.c_str(), lineCharCount);
			}
			else {
				// �����I�ɕ\������
				talk(430, y, line.c_str(), totalCharCount - charCounter);
				break; // ����ȏ�\�����镶�����Ȃ��̂Ń��[�v�𔲂���
			}
			charCounter += lineCharCount; // ���̍s�̕��������J�E���^�[�ɒǉ�
			y += FONT_SIZE;
		}
	}

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

//1������������\���@�S�p���p�Ή�
void GameOverScene::talk(int x, int y, const char* t, int availableChars) const {

	////�t�H���g�ւ��鎞�Ɏg���@���͎g��Ȃ�
    int fontHandle = CreateFontToHandle("dotfont", 15, -2);
   ChangeFont("dotfont"); // �t�H���g��ݒ�

	int color = GetColor(255, 255, 255);//�F	
	int length = strlen(t); // ������̒������擾

	for (int i = 0; i < availableChars && i < length; i++) {
		int Size = GetCharBytes(DX_CHARCODEFORMAT_SHIFTJIS, t + i);
		if (t[i] == '\n') { // ���s���������o
			y += FONT_SIZE; // y���W���X�V���ĉ��s
			x = 100; // x���W�����Z�b�g
		}
		else if (Size == 1) { // ���p����
			DrawFormatString(x, y, color, "%c", t[i]);
			x += FONT_SIZE/2; // ���̕����̂��߂�X���W���X�V
		}
		else { // �S�p����
			DrawFormatString(x, y, color, "%c%c", t[i], t[i + 1]);
			x += FONT_SIZE; // �S�p�����̂��߂�X���W���X�V
			i++; // �S�p������2�o�C�g�Ȃ̂ŃC���f�b�N�X��1�ǉ��ŃX�L�b�v
		}
	}
}

SCENE_TYPE GameOverScene::GetNowScene() const {
	return SCENE_TYPE::GAME_OVER;
}
