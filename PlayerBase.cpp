#include"DxLib.h"
#include"Stage.h"
#include"Key.h"

#define PLAYER_SIZE_X 30.0f//�T�C�Y
#define PLAYER_SIZE_Y 50.0f//�T�C�Y

#define WALK_SPEED 3.0f//1�t���[���Ői�ޑ���

#define JUMP_SPEED 7.0f//1�t���[���ŃW�����v���鍂��

#define ACCELERATION 0.15f//�������̉���

#define CHARACTER_DISTANCE 90.0f//�L�����N�^�[���m�̋���

#define IMAGE_CHANGE_TIME 0.15f//�摜�؂�ւ��̎���(�b��)
#define PLAYER_IMAGE_NUM 4//�v���C���[�摜�̎��

PlayerBase::PlayerBase(PLAYER_JOB player_job) : CharacterBase({ 90.0f, 200.0f }, { PLAYER_SIZE_X, PLAYER_SIZE_Y }, 50, 10, 5, 5),
player_job(player_job),image_change_time(0.0f),draw_image_num(0), 
is_leader(false), is_casket_fall(false), is_party_member(true), is_set_casket(false)
{
    //�W�����v�̋L�^�����Z�b�g
    for (int i = 0; i < JUMP_LOG; i++)jump_log[i] = false;

    is_facing_left = false;

    if (LoadDivGraph("image/Player/casket.png", 5, 5, 1, 50, 50, player_image[2]) == -1)throw("image/Player/casket.png���ǂݍ��߂܂���\n");

    OutputDebugString("PlayerBase�R���X�g���N�^�Ă΂�܂����B\n");
}

PlayerBase::~PlayerBase()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 5; j++)DeleteGraph(player_image[i][j]);
    }

    OutputDebugString("PlayerBase�f�X�g���N�^���Ă΂�܂����B\n");
}


bool PlayerBase::Update(float delta_time, PlayerBase* previous_player)
{
    //�p�[�e�B�̐؂藣��
    if (Key::KeyDown(KEY_TYPE::R))
    {
        is_party_member = !is_party_member;
        for (int i = 0; i < JUMP_LOG; i++)jump_log[i] = false;
    }
    
    //�L�������擪���H
    if (previous_player == nullptr)is_leader = true;
    else is_leader = false;

    //�v���C���[�摜�̐؂�ւ�
    if ((image_change_time += delta_time) > IMAGE_CHANGE_TIME)
    {
        if (!is_dead || speed.x != 0.0f)
        {
            if (++draw_image_num >= PLAYER_IMAGE_NUM)draw_image_num = 0;
        }
        image_change_time = 0.0f;
    }

    //�L�����N�^�[�̍��W�X�V
    if (is_leader)
    {
        //�擪�L�����̏ꍇ
        UpdateLeader();
    }
    else
    {
        //�擪�L�����ȊO�̏ꍇ
        UpdateFollower(previous_player);
    }

    //�L���������񂾏ꍇ
    if (location.y > SCREEN_HEIGHT)is_set_casket = true;
    else if ((location.x > stage->GetCenterLocationX() + 800.0f) || (location.x < stage->GetCenterLocationX() - 800.0f))is_set_casket = true;

    if(is_set_casket)
    {
        //�擪�L�����̐^��ɗ��Ƃ�
        location.x = player_manager->GetPlayerLocation().x;
        location.y = -400.f;

        //�����Ă����Ԃɂ���
        is_casket_fall = true;

        //���S��Ԃɂ���
        is_dead = true;
        
        //hp��0�ɂ���
        hp = 0;

        //�����ɂ��邩�̃t���O��false�ɂ���
        is_set_casket = false;

        return true;
    }

    return false;
}


////�擪�L�����̍X�V//////

void PlayerBase::UpdateLeader()
{

    //�����U��(B�{�^�����͎�)

    if (Key::KeyDown(KEY_TYPE::B))
    {
        if (is_facing_left)
        {
            //���ɍU��
            attack_manager->AddPlayerAttack({ location.x - 50.0f, location.y }, { 40.0f,40.0f }, { 0.0f,0.0f }, 0.1f, 3, ATTACK_TYPE::EXPLOSION, 1.0f);
        }
        else
        {
            //�E�ɍU��
            attack_manager->AddPlayerAttack({ location.x + 50.0f, location.y }, { 40.0f,40.0f }, { 0.0f,0.0f }, 0.1f, 3, ATTACK_TYPE::EXPLOSION, 1.0f);
        }
    }

    //�U��2(Y�{�^�����͎�)

    else if (Key::KeyDown(KEY_TYPE::Y))
    {
        if (is_facing_left)
        {
            //���ɍU��
            attack_manager->AddPlayerAttack(location, { 10.0f,10.0f }, { -8.0f,0.0f }, 5.0f, 3, ATTACK_TYPE::FIRE_BALL, 2.0f);
        }
        else
        {
            //�E�ɍU��
            attack_manager->AddPlayerAttack(location, { 10.0f,10.0f }, { 8.0f,0.0f }, 5.0f, 3, ATTACK_TYPE::FIRE_BALL, 2.0f);
        }
    }

   
    //////X���W�̍X�V////////


    //���E�L�[���͂��ꂽ�ꍇ�A���̕����ɐi�߂�

    if (Key::KeyPressed(KEY_TYPE::LEFT))
    {
        if ((speed.x -= ACCELERATION) < -WALK_SPEED) speed.x = -WALK_SPEED;
    }
    else if (Key::KeyPressed(KEY_TYPE::RIGHT))
    {
        if ((speed.x += ACCELERATION) > WALK_SPEED)speed.x = WALK_SPEED;
    }

    //���E�L�[�����͂���Ă��Ȃ��ꍇ�A���X�ɃX�s�[�h�𗎂Ƃ�
    else
    {
        if (speed.x < 0.0f)
        {
            if ((speed.x += ACCELERATION) > 0.0f) speed.x = 0.0f;
        }
        else if (speed.x > 0.0f)
        {
            if ((speed.x -= ACCELERATION) < 0.0f)speed.x = 0.0f;
        }
    }

    //���W�̉��Z
    location.x += speed.x;

    //�u���b�N�ɓ������Ă���ꍇ
    if (stage->HitBlock(this))
    {
        //���W�𒲐�
        location.x = roundf(location.x);
        while (stage->HitBlock(this))location.x -= (speed.x / fabsf(speed.x));
        speed.x = 0.0f;
    }

    //���E�ǂ���ɐi��ł��邩�H
    if (speed.x < 0.0f)is_facing_left = true;
    else if (speed.x > 0.0f)is_facing_left = false;


    /////Y���W�̍X�V/////////////


    //�W�����v�������H
    bool is_jump = false;

    //�d�͂̉��Z
    if((speed.y += GRAVITY) > JUMP_SPEED)speed.y = JUMP_SPEED;

    //���W�̉��Z
    location.y += speed.y;

    //�u���b�N�ɓ��������ꍇ
    if (stage->HitBlock(this))
    {
        //���W�̒���
        location.y = roundf(location.y);
        while (stage->HitBlock(this))location.y -= (speed.y / fabsf(speed.y));

        //�n�ʂɓ������Ă���ꍇ
        if (speed.y > 0.0f)
        {
            if (Key::KeyDown(KEY_TYPE::A))
            {
                speed.y = -JUMP_SPEED;//A�{�^���ŃW�����v
                is_jump = true;
            }
            else speed.y = 0.0f;
        }
        else
        {
            speed.y = 0.0f;//���Ƀu���b�N���������Ă���ꍇ�AY�̃X�s�[�h��0�ɂ���
            draw_image_num = 4;
        }
    }
    else draw_image_num = 4;

    //�W�����v�������Ƃ��L�^����
    if(is_party_member)SetJumpLog(is_jump);
}


///�擪�L�����ȊO�̍X�V/////////

void PlayerBase::UpdateFollower(PlayerBase* previous_player)
{
    ////X���W�̍X�V////////

    //�����ŋ󂩂�~���Ă���
    if (is_casket_fall)
    {
        //x���W�͓������Ȃ�
        speed.x = 0.0f;
    }

    //��������Ȃ��Ƃ�
    else
    {
        //�p�[�e�B��ԂŁA�O�̃L�����Ɨ���Ă����瓮��
        if ((is_party_member) && (previous_player->GetLocation().x > location.x) && ((previous_player->GetLocation().x - location.x) > CHARACTER_DISTANCE))
        {
            if ((speed.x += ACCELERATION) > WALK_SPEED)speed.x = WALK_SPEED;
        }
        else if ((is_party_member) && (previous_player->GetLocation().x < location.x) && ((location.x - previous_player->GetLocation().x) > CHARACTER_DISTANCE))
        {
            if ((speed.x -= ACCELERATION) < -WALK_SPEED)speed.x = -WALK_SPEED;
        }

        //���X�Ɏ~�܂�
        else
        {
            if (speed.x < 0.0f)
            {
                if ((speed.x += ACCELERATION) > 0.0f) speed.x = 0.0f;
            }
            else if (speed.x > 0.0f)
            {
                if ((speed.x -= ACCELERATION) < 0.0f)speed.x = 0.0f;
            }
        }
    }

    //���W�̉��Z
    location.x += speed.x;

    //�u���b�N�ɓ������Ă���ꍇ
    if (stage->HitBlock(this))
    {
        //���W�𒲐�
        location.x = roundf(location.x);
        while (stage->HitBlock(this))location.x -= (speed.x / fabsf(speed.x));
        speed.x = 0.0f;
    }

    //���E�ǂ���ɐi��ł��邩�H
    if (speed.x < 0.0f)is_facing_left = true;
    else if (speed.x > 0.0f)is_facing_left = false;


    ////Y���W�̍X�V/////////////////

    //�W�����v�������H
    bool is_jump = false;

    //�d�͂̉��Z
    if (is_casket_fall)speed.y = JUMP_SPEED * 1.5;
    else if ((speed.y += GRAVITY) > JUMP_SPEED)speed.y = JUMP_SPEED;

    //���W�̉��Z
    location.y += speed.y;

    //�u���b�N�ɓ��������ꍇ
    if (stage->HitBlock(this))
    {
        //���W�̒���
        location.y = roundf(location.y);
        while (stage->HitBlock(this))location.y -= (speed.y / fabsf(speed.y));

        //�n�ʂɓ������Ă���ꍇ
        if (speed.y > 0.0f)
        {
            if (is_casket_fall)is_casket_fall = false;

            if (previous_player->GetJumpLog())speed.y = -JUMP_SPEED;
            else speed.y = 0.0f;
        }
        else
        {
            speed.y = 0.0f;//���Ƀu���b�N���������Ă���ꍇ�AY�̃X�s�[�h��0�ɂ���
            draw_image_num = 4;
        }
    }
    else draw_image_num = 4;

    SetJumpLog(previous_player->GetJumpLog());
}

//�_���[�W������������
bool PlayerBase::HitDamege(BoxCollider* bc, int attack_power)
{
    if (!is_dead)
    {
        if ((hp -= attack_power) <= 0)
        {
            hp = 0;
            attack_manager->AddPlayerAttack(location, { 0.0f,0.0f }, { 0.0f,0.0f }, -1.0f, 0, ATTACK_TYPE::SMALL_EXPLOSION, 5.0f);
            is_set_casket = true;
            
        }
        else if (location.x > bc->GetLocation().x)speed.x = 5.0f;
        else speed.x = -5.0f;
    }
    return is_dead;
}

void PlayerBase::SetJumpLog(bool is_jump)
{
    for (int i = 0; i < JUMP_LOG; i++)
    {
        if (i == JUMP_LOG - 1)jump_log[i] = is_jump;
        else jump_log[i] = jump_log[i + 1];
    }
}

bool PlayerBase::GetJumpLog()const
{
    return jump_log[0];
}

bool PlayerBase::GetIsLeader()const
{
    return is_leader;
}

PLAYER_JOB PlayerBase::GetPlayerJob()const
{
    return player_job;
}

void PlayerBase::Draw() const
{
    DATA draw_location = { location.x + stage->GetCameraWork(), location.y };

    int draw_image_type = (speed.x == 0.0f);
    if (is_dead)draw_image_type = 2;

    DrawRotaGraph(draw_location.x, draw_location.y, 2.0, 0, player_image[draw_image_type][draw_image_num], TRUE, is_facing_left);
    //DrawBox(draw_location.x - radius.x, draw_location.y - radius.y, draw_location.x + radius.x, draw_location.y + radius.y, 0xffffff, FALSE);

    //DrawRotaGraph(stage->GetCameraWork() + (), 500, 1, 0, player_image[0][0], TRUE);
    //DrawFormatString(0, 500, 0xffffff, "%f", (-stage->GetCameraWork() + 600));
}