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

PlayerManager::PlayerManager() : stage(stage), draw_arrow_time(0.0f), message(nullptr), ui(nullptr)
{
	if ((arrow_image = LoadGraph("image/Player/arrow.png")) == -1)throw("image/Player/arrow.png���ǂݍ��߂܂���\n");

	OutputDebugString("PlayerManager�R���X�g���N�^�Ă΂�܂����B\n");
}

void PlayerManager::Initialize(class Stage* stage, class EnemyManager* enemy_manager, class AttackManager* attack_manager)
{
	this->stage = stage;
	this->enemy_manager = enemy_manager;
	this->attack_manager = attack_manager;

	player[0] = new Hero({300, 407}, stage, this, enemy_manager, attack_manager);//�E��
	player[1] = new Warrior({ 550, 407 }, stage, this, enemy_manager, attack_manager);//��m
	player[2] = new Wizard({ 620, 407 }, stage, this, enemy_manager, attack_manager);//���@�g��
	player[3] = new Monk({ 690, 407 }, stage, this, enemy_manager, attack_manager); //�m��

	ui = new Ui(player);
}

PlayerManager::~PlayerManager()
{
	for (int i = 0; i < PLAYER_NUM; i++)delete player[i];
	delete ui;
	delete message;

	OutputDebugString("PlayerManager�f�X�g���N�^���Ă΂�܂����B\n");
}

bool PlayerManager::Update(float delta_time)
{
	//�擪�L�����؂�ւ����̖��̕\������
	if ((draw_arrow_time += delta_time) > DRAW_ARROW_TIME)draw_arrow_time = DRAW_ARROW_TIME;

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

	if (message == nullptr)
	{
		//L�{�^���Ńv���C���[���בւ�
		if (Key::KeyDown(KEY_TYPE::L))PlayerSorting();
		//R�{�^���Ńp�[�e�B�[�؂藣��
		if (Key::KeyDown(KEY_TYPE::R))SetPartyState(!player[0]->GetIsPartyMember());
	}
	
	if (message != nullptr)
	{
		if (message->Update(delta_time))
		{
			delete message;
			message = nullptr;
		}
	}

	ui->Update();

	return false;
}

void PlayerManager::SetPartyState(bool party_state)
{
	for (int i = 0; i < PLAYER_NUM; i++)
	{
		player[i]->SetIsPartyMember(party_state);
	}
}

void PlayerManager::AddPlayerHp(int add_hp)
{
	for (int i = 0; i < PLAYER_NUM; i++)player[i]->AddHp(add_hp);
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

	ui->Draw();

	if (message != nullptr)message->Draw();
}

void PlayerManager::SetMessage(const char* text_data_name)
{
	if (message == nullptr)message = new Message(text_data_name);
}

bool PlayerManager::GetiIsTalking()const
{
	return (message != nullptr);
}