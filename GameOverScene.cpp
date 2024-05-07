#include "GameOverScene.h"
#include "Key.h"
#include "DxLib.h"

GameOverScene::GameOverScene() {
    FileHandle = 0;
    memset(text, 0, sizeof(text));
}

GameOverScene::~GameOverScene() {}

//����������
void GameOverScene::Initialize() {}

//�I��������
void GameOverScene::Finalize() {}

//�X�V����
SCENE_TYPE GameOverScene::Update(float delta_time) {
    if (Key::KeyDown(KEY_TYPE::A)) return SCENE_TYPE::MAIN;

    // file.txt���J��
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
            if (ProcessMessage() != 0) break; // �L�[�������ꂽ�烋�[�v�𔲂���
        }
        if (ProcessMessage() != 0) break; // �L�[�������ꂽ�烋�[�v�𔲂���
        draw_y += 20;
    }

    // �L�[���͑҂�
    while (!ProcessMessage()) {
        if (CheckHitKey(KEY_INPUT_A)) {
            break;
        }
    }

    // �t�@�C�������
    FileRead_close(FileHandle);

    // ���l�̏�����file2.txt�ɑ΂��čs��
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
            if (ProcessMessage() != 0) break; // �L�[�������ꂽ�烋�[�v�𔲂���
        }
        if (ProcessMessage() != 0) break; // �L�[�������ꂽ�烋�[�v�𔲂���
        draw_y += 20;
    }

    // �L�[���͑҂�
    while (!ProcessMessage()) {
        if (CheckHitKey(KEY_INPUT_A)) {
            break;
        }
    }

    // �t�@�C�������
    FileRead_close(FileHandle);

    // ���l�̏�����file3.txt�ɑ΂��čs��
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
            if (ProcessMessage() != 0) break; // �L�[�������ꂽ�烋�[�v�𔲂���
        }
        if (ProcessMessage() != 0) break; // �L�[�������ꂽ�烋�[�v�𔲂���
        draw_y += 20;
    }

    // �L�[���͑҂�
    while (!ProcessMessage()) {
        if (CheckHitKey(KEY_INPUT_A)) {
            break;
        }
    }

    // �t�@�C�������
    FileRead_close(FileHandle);

    return GetNowScene();
}

//�`�揈��
void GameOverScene::Draw() const 
{


}

void GameOverScene::talk(int x, int y, const char t[], int nCount) {
    int n = nCount / 15;

    int fontHandle = CreateFontToHandle("dotfont", 15, -1);
    ChangeFont("dotfont"); //�t�H���g��ݒ�

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

    //�t�H���g�n���h�����폜
    DeleteFontToHandle(fontHandle);
}

//���݂̃V�[�������擾
SCENE_TYPE GameOverScene::GetNowScene() const {
    return SCENE_TYPE::GAME_OVER;
}
