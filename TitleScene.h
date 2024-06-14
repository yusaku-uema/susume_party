#pragma once
#include "SceneBase.h"

#define MENU_NUM 4

class TitleScene : public SceneBase
{
private:
    static const int CHARACTER_COUNT = 4; // �L�����N�^�[�̐���4�ɕύX
    int characterImages[CHARACTER_COUNT][5];
    int currentFrames[CHARACTER_COUNT];
    int frameCounts[CHARACTER_COUNT];
    int frameWidth;
    int frameHeight;
    int scaleFactor;

    static int scrollX; // �w�i�̃X�N���[���ʂ�ÓI�����o�[�Ƃ��Ē�`
    static int logoX; // ���S��X���W��ÓI�����o�[�Ƃ��Ē�`
    static int background_images[2]; // �w�i�摜�̃n���h����ÓI�����o�[�Ƃ��Ē�`
    int logo_image;//�^�C�g�����S

    int menu_image[MENU_NUM][2];//���j���[�摜
    int num_image[4];
    int set_menu_image[8];
    int help_image[3]; //�w���v�C���[�W

    int input_time;//���͎�t����
    int select_menu;//���ݓ��͂��Ă��郁�j���[
    int help_menu;
    int credit_image;

    bool can_scene_change;//���̃V�[���ɍs���邩
    bool help;//�w���v��ʂɍs����
    bool credit;//�N���W�b�g
    bool isMenuScrolling;

    static int menuX; // 


 


public:
    TitleScene();
    virtual ~TitleScene();

    virtual void Initialize() override;
    virtual void Finalize() override;

    virtual SCENE_TYPE Update(float delta_time) override;
    virtual void Draw() const override;

    virtual SCENE_TYPE GetNowScene() const override;
};
