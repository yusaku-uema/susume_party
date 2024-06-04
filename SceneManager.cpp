#include"DxLib.h"
#include"SceneManager.h"
#include"TitleScene.h"
#include"TalkUi.h"
#include"GameMainScene.h"
#include"GameOverScene.h"
#include"Key.h"


SceneManager::SceneManager() : current_scene(nullptr)
{
}

SceneManager::~SceneManager()
{	
}

//�V�[���}�l�W���[�@�\:����������
void SceneManager::Initialize()
{
	//�E�B���h�E�̃^�C�g����ݒ�
	SetMainWindowText("�i��!!�p�[�e�B");

	//�E�B���h�E���[�h�ŋN��
	if (ChangeWindowMode(TRUE) != DX_CHANGESCREEN_OK)
	{
		throw("�E�B���h�E���[�h�ŋN���ł��܂���ł���\n");
	}

	SetGraphMode(1280, 720, 32);

	//DX���C�u�����̏�����
	if (DxLib_Init() == -1)
	{
		throw("Dx���C�u�������������ł��܂���ł���\n");
	}

	//�`���w�菈��
	if (SetDrawScreen(DX_SCREEN_BACK) == -1)
	{
		throw("�`���̎w�肪�ł��܂���ł���\n");
	}

	//�^�C�g���V�[������n�߂�
	ChangeScene(SCENE_TYPE::MAIN);
}

//�V�[���}�l�[�W���[�@�\:�X�V����
void SceneManager::Update()
{
	int delta_second = 1000 / 60;
	int delta_time = 0.0f;

	while (ProcessMessage() != -1)//���C�����[�v
	{
		int start_time = GetNowCount();

		// ���͍X�V
		Key::Update();

		//�X�V����
		SCENE_TYPE next_scene = current_scene->Update((float)delta_time / 1000);

		//�G���h���I������Ă�����Q�[�����I������
		if (next_scene == SCENE_TYPE::GAME_END)break;

		//���݂̃V�[���Ǝ��̃V�[��������Ă�����V�[����ς���
		if (next_scene != current_scene->GetNowScene())ChangeScene(next_scene);

		//�`�揈��
		Draw();

		if (delta_second > (GetNowCount() - start_time))WaitTimer(delta_second - (GetNowCount() - start_time));
		delta_time = GetNowCount() - start_time;
	}
}

//�V�[���}�l�[�W���[�@�\�F�I��������
void SceneManager::Finalize()
{
	//�V�[�����̍폜
	if (current_scene != nullptr)
	{
		current_scene->Finalize();
		delete current_scene;
		current_scene = nullptr;
	}

	//DX���C�u�����̎g�p���I������
	DxLib_End();
}

//�V�[���}�l�[�W���[�@�\�F�`�揈��
void SceneManager::Draw() const
{
	ClearDrawScreen();//��ʂ̏�����

	current_scene->Draw();//�V�[���̕`��

	ScreenFlip();//����ʂ̓��e��\��ʂɔ��f
}

void SceneManager::ChangeScene(SCENE_TYPE scene_type)//�V�[���؂�ւ�����
{
	//�V�[���𐶐�����
	SceneBase* new_scene = CreateScene(scene_type);

	if (new_scene == nullptr)throw("�V�[���������ł��܂���ł����B\n");//�G���[�`�F�b�N
	
	if (current_scene != nullptr)//�O��V�[���̏I�����������s��
	{
		current_scene->Finalize();
		delete current_scene;
	}

	new_scene->Initialize();//�V�������������V�[���̏��������s��

	current_scene = new_scene;//���݂̃V�[���̍X�V(����ւ�)
}

//�V�[����������
SceneBase* SceneManager::CreateScene(SCENE_TYPE scene_type)
{
	//�����i�V�[���^�C�v�j�ɂ���āA��������V�[�������肷��
	switch (scene_type)
	{
	case SCENE_TYPE::TITLE:
		return new TitleScene;
	case SCENE_TYPE::TALKUI:
		return new TalkUi;
	case SCENE_TYPE::MAIN:
		return new GameMainScene;
	case SCENE_TYPE::GAME_OVER:
		return new GameOverScene;
	case SCENE_TYPE::ENDING:
	default:
		return nullptr;
	}
}