#include "DxLib.h"
#include"SceneManager.h"


// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,_In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	//��O�����i�ُ킪����������Acatch���ɔ�т܂��j
	try
	{
		//�V�[���}�l�[�W���[�@�\�̐���
		SceneManager manager;

		//�V�[���}�l�[�W���[�@�\�̏���������
		manager.Initialize();

		//�V�[���}�l�[�W���[�@�\�̍X�V����
		manager.Update();

		//�V�[���}�l�[�W���[�@�\�̏I��������
		manager.Finalize();
	}
	catch (const char* err_log)
	{
		//�G���[�������e�̏o��
		OutputDebugString(err_log);

		//�G���[�I����ʒm
		return -1;
	}

	return 0;				// �\�t�g�̏I�� 
}