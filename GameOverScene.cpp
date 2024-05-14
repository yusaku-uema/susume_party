#include "GameOverScene.h"
#include "Key.h"
#include "DxLib.h"
#include <fstream>
#include <codecvt>  // for codecvt_utf8
#include <locale>   // for wstring_convert

GameOverScene::GameOverScene() {
    // �Q�[���I�[�o�[�摜�̓ǂݍ���
    if ((gameover_image = LoadGraph("image/GameOver/gameover.png")) == -1)
        throw("�Q�[���I�[�o�[�摜�Ǎ��ݎ��s\n");

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

// ����������
void GameOverScene::Initialize() {}

// �I��������
void GameOverScene::Finalize() {}

// �X�V����
SCENE_TYPE GameOverScene::Update(float delta_time) {
    frameCount++;  // �t���[���J�E���g���X�V

    if (transparency < 255) {
        transparency += transparencySpeed;
    }
    else if (transparency == 255 && !textLoaded) {
        textLoaded = true;
        LoadText();
    }

    return GetNowScene();
}

// �`�揈��
void GameOverScene::Draw() const {
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, transparency);
    DrawGraph(imagePosX, imagePosY, gameover_image, TRUE);

    if (transparency == 255) {
        int y = 300;
        for (const auto& line : textLines) {
            talk(100, y, line.c_str(), frameCount);  // `talk`���g�p���ăe�L�X�g��`��
            y += 20;
        }
    }

    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void GameOverScene::talk(int x, int y, const char* t, int frameCount) const {
    int color = GetColor(255, 255, 255);
    int length = strlen(t); // ������̒������擾
    int charCount = frameCount / 15; // 15�t���[�����Ƃ�1�������\��

    for (int i = 0; i < charCount && t[i] != '\0'; i++) {
        int Size = GetCharBytes(DX_CHARCODEFORMAT_SHIFTJIS, t + i);
        if (Size == 1) { // ���p����
            DrawFormatString(x, y, color, "%c", t[i]);
            x += 9; // ���̕����̂��߂�X���W���X�V
        }
        else { // �S�p����
            DrawFormatString(x, y, color, "%c%c", t[i], t[i + 1]);
            x += 17; // �S�p�����̂��߂�X���W���X�V
            i++; // �S�p������2�o�C�g�Ȃ̂ŃC���f�b�N�X��1�ǉ��ŃX�L�b�v
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

// ���݂̃V�[�������擾
SCENE_TYPE GameOverScene::GetNowScene() const {
    return SCENE_TYPE::GAME_OVER;
}
