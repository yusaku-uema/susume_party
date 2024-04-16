#pragma once
#include"SceneBase.h"

#define FREAM_RATE (60)//�t���[�����[�g
#define DELTA_SECOND  (1000 / FREAM_RATE)//1�t���[��������̎���

class SceneManager//�V�[���}�l�[�W���[�N���X
{
private:
	SceneBase* current_scene;   //���݃V�[��

public:
	SceneManager() ;
	~SceneManager();

	void Initialize();  //����������
	void Finalize();    //�I��������
	void Update() ;      //�X�V����
	

private:
	void Draw() const;   //�`�揈��
	void ChangeScene(SCENE_TYPE scene_type);  //�V�[���؂�ւ�����
	SceneBase* CreateScene(SCENE_TYPE scene_type); //�V�[����������
};