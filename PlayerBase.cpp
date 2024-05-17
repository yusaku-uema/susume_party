#include"DxLib.h"
#include"PlayerBase.h"
#include"Key.h"

#define PLAYER_SIZE_X 30.0f//�T�C�Y
#define PLAYER_SIZE_Y 50.0f//�T�C�Y

#define WALK_SPEED 3.0f//1�t���[���Ői�ޑ���

#define JUMP_SPEED 8.0f//1�t���[���ŃW�����v���鍂��

#define ACCELERATION 0.15f//�������̉���

#define CHARACTER_DISTANCE 90.0f//�L�����N�^�[���m�̋���

#define IMAGE_CHANGE_TIME 0.15f//�摜�؂�ւ��̎���(�b��)
#define PLAYER_IMAGE_NUM 4//�v���C���[�摜�̎��

PlayerBase::PlayerBase(class Stage* stage) : CharacterBase({ 90.0f, 200.0f }, { PLAYER_SIZE_X, PLAYER_SIZE_Y }, 20, 10, 5, 5),
stage(stage), is_dead(false), is_facing_left(false), image_change_time(0.0f), draw_image_num(0)
{
    draw_image_num = GetRand(3);
    for (int i = 0; i < JUMP_LOG; i++)jump_log[i] = false;
    OutputDebugString("PlayerBase�R���X�g���N�^�Ă΂�܂����B\n");
}

PlayerBase::~PlayerBase()
{
    OutputDebugString("PlayerBase�f�X�g���N�^���Ă΂�܂����B\n");
}

void PlayerBase::Update(float delta_time, PlayerBase* previous_player)
{
    //�擪�L���������Ȃ��ꍇ
    if (previous_player == nullptr)UpdateLeader();
    else UpdateFollower(previous_player);

    if ((image_change_time += delta_time) > IMAGE_CHANGE_TIME)
    {
        if (++draw_image_num >= PLAYER_IMAGE_NUM)draw_image_num = 0;
        image_change_time = 0.0f;
    }
    
    if (location.y > 600.0f)is_dead = false;
}


void PlayerBase::UpdateLeader()
{
    //�U��
    if (Key::KeyDown(KEY_TYPE::B))stage->AddAttack(location, { 10,10 }, { 5,0 }, 5.0, 3, 0);

    //X���W�̍X�V

    if (Key::KeyPressed(KEY_TYPE::LEFT))//����������Ă�Ȃ獶�ɐi��
    {
        if ((speed.x -= ACCELERATION) < -WALK_SPEED) speed.x = -WALK_SPEED;
    }
    else if (Key::KeyPressed(KEY_TYPE::RIGHT))//�E��������Ă�Ȃ�E�ɐi��
    {
        if ((speed.x += ACCELERATION) > WALK_SPEED)speed.x = WALK_SPEED;
    }
    else//����������Ă��Ȃ����́A���X�ɃX�s�[�h�𗎂Ƃ�
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
    }

    //���E�ǂ���ɐi��ł��邩�H
    if (speed.x < 0.0f)is_facing_left = true;
    else if (speed.x > 0.0f)is_facing_left = false;


    //Y���W�̍X�V

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
        else speed.y = 0.0f;//���Ƀu���b�N���������Ă���ꍇ�AY�̃X�s�[�h��0�ɂ���
    }

    SetJumpLog(is_jump);
}

void PlayerBase::UpdateFollower(PlayerBase* previous_player)
{
    //X���W�̍X�V

    if ((previous_player->GetLocation().x > location.x) && ((previous_player->GetLocation().x - location.x) > CHARACTER_DISTANCE))
    {
        if ((speed.x += ACCELERATION) > WALK_SPEED)speed.x = WALK_SPEED;
    }
    else if ((previous_player->GetLocation().x < location.x) && ((location.x - previous_player->GetLocation().x) > CHARACTER_DISTANCE))
    {
        if ((speed.x -= ACCELERATION) < -WALK_SPEED)speed.x = -WALK_SPEED;
    }
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
    }

    //���E�ǂ���ɐi��ł��邩�H
    if (speed.x < 0.0f)is_facing_left = true;
    else if (speed.x > 0.0f)is_facing_left = false;


    //Y���W�̍X�V

    //�W�����v�������H
    bool is_jump = false;

    //�d�͂̉��Z
    if ((speed.y += GRAVITY) > JUMP_SPEED)speed.y = JUMP_SPEED;

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
            if (previous_player->GetJumpLog())speed.y = -JUMP_SPEED;
            else speed.y = 0.0f;
        }
        else speed.y = 0.0f;//���Ƀu���b�N���������Ă���ꍇ�AY�̃X�s�[�h��0�ɂ���
    }

    SetJumpLog(previous_player->GetJumpLog());
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

bool PlayerBase::GetIsDead()const//�v���C���[������ł��邩�H
{
    return is_dead;
}

void PlayerBase::Draw(float camera_work) const
{
    DATA draw_location = { location.x + camera_work, location.y };

    if ((draw_location.x >= -radius.x) && (draw_location.x <= SCREEN_WIDTH + radius.x))
    {
        bool is_wait = (speed.x == 0.0f);
        DrawRotaGraph(draw_location.x, draw_location.y, 2.0, 0, player_image[is_wait][draw_image_num], TRUE, is_facing_left);
        //DrawBox(draw_location.x - radius.x, draw_location.y - radius.y, draw_location.x + radius.x, draw_location.y + radius.y, 0xffffff, FALSE);
    }

    DrawFormatString(0, 500, 0xffffff, "%f", location.y);
}