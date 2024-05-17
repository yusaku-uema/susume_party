#include"DxLib.h"
#include"PlayerBase.h"
#include"Key.h"

#define PLAYER_SIZE_X 30.0f//�T�C�Y
#define PLAYER_SIZE_Y 60.0f//�T�C�Y
#define WALK_SPEED 3.0f//1�t���[���Ői�ޑ���
#define JUMP_SPEED 8.0f//1�t���[���ŃW�����v���鍂��
#define ACCELERATION 0.15f//�������̉���
#define CHARACTER_DISTANCE 80.0f//�L�����N�^�[���m�̋���

#define IMAGE_CHANGE_TIME 0.15f//�摜�؂�ւ��̎���(�b��)
#define PLAYER_IMAGE_NUM 4//�v���C���[�摜�̎��

PlayerBase::PlayerBase() : CharacterBase({ 90.0f, 200.0f }, { PLAYER_SIZE_X, PLAYER_SIZE_Y }, 20, 10, 5, 5), 
is_dead(false), is_facing_left(false), image_change_time(0.0f), draw_image_num(1)
{
    for (int i = 0; i < JUMP_LOG; i++)jump_log[i] = false;
    OutputDebugString("PlayerBase�R���X�g���N�^�Ă΂�܂����B\n");
}

PlayerBase::~PlayerBase()
{
    OutputDebugString("PlayerBase�f�X�g���N�^���Ă΂�܂����B\n");
}

void PlayerBase::Update(float delta_time, class Stage* stage, PlayerBase* previous_player)
{

    if (Key::KeyDown(KEY_TYPE::B) && previous_player == nullptr)stage->AddAttack(location, { 10,10 }, { 5,0 }, 5.0, 3, 0);
    //x���W�̍X�V
    MoveX(stage, previous_player);

    location.x += speed.x;//���W�̉��Z
    
    if (speed.x == 0.0f)draw_image_num = 1;
    else
    {
        if ((image_change_time += delta_time) > IMAGE_CHANGE_TIME)
        {
            if (++draw_image_num >= PLAYER_IMAGE_NUM)draw_image_num = 0;
            image_change_time = 0.0f;
        }
        if (speed.x < 0.0f)is_facing_left = true;//���ɐi��ł���Ȃ�is_facing_left��true�ɂ���
        else if (speed.x > 0.0f)is_facing_left = false;//�E�ɐi��ł���Ȃ�is_facing_left��false�ɂ���
    }
   

    if (stage->HitBlock(this))//�u���b�N�ɓ������Ă���ꍇ�A���W�𒲐�
    {
        location.x = roundf(location.x);//���W�𐮐��l�ɂ���
        while (stage->HitBlock(this))location.x -= (speed.x / fabsf(speed.x));//�u���b�N�ɓ������Ă���ԁA�i�s�����Ƃ͋t�ɐi�߂�
    }

    //y���W�̍X�V
    MoveY(stage, previous_player);

    if (location.y > 600.0f)is_dead = false;
}

void PlayerBase::MoveX(class Stage* stage, PlayerBase* player)
{
    if (player == nullptr)
    {
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
    }
    else
    {
        if ((player->GetLocation().x > location.x) && ((player->GetLocation().x - location.x) > CHARACTER_DISTANCE))
        {
            if ((speed.x += ACCELERATION) > WALK_SPEED)speed.x = WALK_SPEED;
        }
        else if ((player->GetLocation().x < location.x) && ((location.x - player->GetLocation().x) > CHARACTER_DISTANCE))
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
    }
}

//y���W�̍X�V
void PlayerBase::MoveY(class Stage* stage, PlayerBase* previous_player)
{
    bool is_jump = false;

    speed.y += GRAVITY;//�d�͂̉��Z
    if (speed.y > JUMP_SPEED)speed.y = JUMP_SPEED;//�d�͂���萔���z���Ȃ��悤�ɂ���
    location.y += speed.y;//���W�̉��Z

    if (stage->HitBlock(this))//�����u���b�N�ɓ������Ă�����i�n�ʂ����ɓ������Ă���j
    {
        location.y = roundf(location.y);//���W�𐮐��l�ɂ���
        while (stage->HitBlock(this))location.y -= (speed.y / fabsf(speed.y));//�u���b�N�ɓ������Ă���ԁA�i�s�����Ƃ͋t�ɐi�߂�

        if (speed.y > 0.0f)//�n�ʂɓ������Ă���ꍇ
        {
            if (previous_player == nullptr)//�擪�L���������Ȃ��ꍇ
            {
                if (Key::KeyDown(KEY_TYPE::A))
                {
                    speed.y = -JUMP_SPEED;//A�{�^���ŃW�����v
                    is_jump = true;
                }
                else speed.y = 0.0f;
            }
            else//�擪�L����������ꍇ
            {
                if (previous_player->GetJumpLog())speed.y = -JUMP_SPEED;
                else speed.y = 0.0f; 
            } 
        }
        else speed.y = 0.0f;//���Ƀu���b�N���������Ă���ꍇ�AY�̃X�s�[�h��0�ɂ���
    }

    if(previous_player == nullptr)SetJumpLog(is_jump);
    else SetJumpLog(previous_player->GetJumpLog());
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
         DrawRotaGraph(draw_location.x, draw_location.y, 2.5, 0, player_image[draw_image_num], TRUE, is_facing_left);
         DrawBox(draw_location.x - radius.x, draw_location.y - radius.y, draw_location.x + radius.x, draw_location.y + radius.y, 0xffffff, FALSE);
    }

    //DrawFormatString(0, 500, 0xffffff, "%f", location.y);
}