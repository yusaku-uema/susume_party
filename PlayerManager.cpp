#include"DxLib.h"
#include"PlayerManager.h"
#include"Key.h"
#include"Stage.h"
#include"Ui.h"
#include"Hero.h"
#include"Warrior.h"
#include"Wizard.h"
#include"Monk.h"

#define DRAW_ARROW_TIME 2.0f//�v���C���[���w�����̕\������

PlayerManager::PlayerManager(class Stage* stage, class AttackManager* attack_manager, class Ui* ui) : stage(stage), draw_arrow_time(0.0f)
{
	player[0] = new Hero(stage, this, attack_manager);//�E��
	player[1] = new Warrior(stage, this, attack_manager);//��m
	player[2] = new Wizard(stage, this, attack_manager);//���@�g��
	player[3] = new Monk(stage, this, attack_manager); //�m��

	ui->SetPlayerPointer(player);

	if ((arrow_image = LoadGraph("image/Player/arrow.png")) == -1)throw("image/Player/arrow.png���ǂݍ��߂܂���\n");

	OutputDebugString("PlayerManager�R���X�g���N�^�Ă΂�܂����B\n");
}

PlayerManager::~PlayerManager()
{
	for (int i = 0; i < PLAYER_NUM; i++)delete player[i];

	OutputDebugString("PlayerManager�f�X�g���N�^���Ă΂�܂����B\n");
}

bool PlayerManager::Update(float delta_time)
{
	//�擪�L�����؂�ւ����̖��̕\������
	if ((draw_arrow_time += delta_time) > DRAW_ARROW_TIME)
		draw_arrow_time = DRAW_ARROW_TIME;

	//���S�L�����̗v�f��
	int dead_player_index = -1;

	//���S�L�������̐�
	int dead_player_count = 0;

	//�X�V�L�����̑O�̃L�������
	PlayerBase* previous_player = nullptr;

    for (int i = 0; i < PLAYER_NUM; i++)
    {
        //�L�����N�^�[�X�V
        if (player[i]->Update(delta_time, previous_player))
        {
            //�L���������񂾂�v�f��������
            dead_player_index = i;
        }

		//�L���������񂾂�J�E���g����
		if (player[i]->GetIsDead())
		{
			dead_player_count++;
		}

		if (dead_player_count >= 4)
		{
			return true;
		}

		//���݂̃L�����̏�������
		previous_player = player[i];
	}

	dead_player_count = dead_player_count;

	DeadPlayerSorting(dead_player_index);

	if (Key::KeyDown(KEY_TYPE::L))
		PlayerSorting();

	return false;
}

void PlayerManager::DeadPlayerSorting(int dead_player_index)//���S�v���C���[���ёւ�
{
	//���S�L����������ꍇ�A����ւ���
	if (dead_player_index != -1)
	{
		PlayerBase* change_player = player[dead_player_index];

		for (int i = dead_player_index; i < PLAYER_NUM; i++)
		{
			if (i == PLAYER_NUM - 1)
			{
				player[i] = change_player;
				if (player[i]->GetIsLeader())draw_arrow_time = 0.0f;
			}
			else player[i] = player[i + 1];
		}
	}
}

void PlayerManager::PlayerSorting()//�v���C���[���ёւ�
{
	//�����Ă���L�����̐��m�F
	int alive_player = 0;
	for (int i = 0; i < PLAYER_NUM; i++)
	{
		if (!player[i]->GetIsDead())alive_player++;
	}

	//�����Ă���L������������A���Ԃ�ς���
	if (alive_player > 0)
	{
		PlayerBase* change_player = player[0];

		for (int i = 0; i < alive_player; i++)
		{
			if (i == alive_player - 1)player[i] = change_player;
			else player[i] = player[i + 1];
		}
		draw_arrow_time = 0.0f;
	}
}

//�U���������������̃`�F�b�N�i����������ture��Ԃ��j
bool PlayerManager::CheckHitDamage(class BoxCollider* bc, int attack_power)
{
	for (int i = 0; i < PLAYER_NUM; i++)
	{
		if ((!player[i]->GetIsDead()) && (player[i]->HitBox(bc)))
		{
			player[i]->HitDamege(bc, attack_power);
			return true;
		}
	}
	return false;
}

PlayerBase* PlayerManager::GetPlayerData()const
{
	return player[0];
}

void PlayerManager::Draw() const
{
	for (int i = PLAYER_NUM - 1; i >= 0; i--)player[i]->Draw();

	if (draw_arrow_time != DRAW_ARROW_TIME)
	{
		DrawRotaGraph(player[0]->GetLocation().x + stage->GetCameraWork(), player[0]->GetLocation().y - 80, 1, 0, arrow_image, TRUE);
	}
}