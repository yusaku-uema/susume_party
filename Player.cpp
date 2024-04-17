#include"DxLib.h"
#include"Player.h"
#include"Key.h"

#define PLAYER_SIZE 30.0f//�T�C�Y
#define WALK_SPEED 1.5f//1�t���[���Ői�ޑ���
#define JUMP_SPEED 8.0f//1�t���[���ŃW�����v���鍂��
#define ACCELERATION 0.1f//�������̉���

Player::Player() : CharacterBase({ 90.0f, 200.0f }, { PLAYER_SIZE, PLAYER_SIZE }, 20, 10, 5, 5),
is_walking(false), is_jump(false), is_facing_left(false)
{
    OutputDebugString("Player�R���X�g���N�^�Ă΂�܂����B\n");
}

Player::~Player()
{
    OutputDebugString("Player�f�X�g���N�^���Ă΂�܂����B\n");
}

void Player::Update(float delta_time, Stage* stage)
{
    //x���W�̍X�V
    if (Key::GetStickAngle(KEY_TYPE::L).x < 0.0f)//����������Ă�Ȃ獶�ɐi��
    {
        if ((speed.x -= ACCELERATION) < -WALK_SPEED) speed.x = -WALK_SPEED;
    }
    else if (Key::GetStickAngle(KEY_TYPE::L).x > 0.0f)//�E��������Ă�Ȃ�E�ɐi��
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

    location.x += speed.x;//���W�̉��Z

    is_walking = true;//�����Ă���ϐ���true�ɂ���
    if (speed.x < 0.0f)is_facing_left = true;//���ɐi��ł���Ȃ�is_facing_left��true�ɂ���
    else if (speed.x > 0.0f)is_facing_left = false;//�E�ɐi��ł���Ȃ�is_facing_left��false�ɂ���
    else is_walking = false;//�ǂ���ɂ��i��ł��Ȃ��Ȃ�����Ă���ϐ���false�ɂ���

    if (stage->HitBlock(this))//�����u���b�N�ɓ������Ă�����
    {
        location.x = roundf(location.x);//���W�𐮐��l�ɂ���
        while (stage->HitBlock(this))location.x -= (speed.x / fabsf(speed.x));//�u���b�N�ɓ������Ă���ԁA�i�s�����Ƃ͋t�ɐi�߂�
    }

    //y���W�̍X�V
    speed.y += GRAVITY;//�d�͂̉��Z
    if (speed.y > FALL_SPEED)speed.y = FALL_SPEED;//�d�͂���萔���z���Ȃ��悤�ɂ���

    location.y += speed.y;//���W�̉��Z

    if (stage->HitBlock(this))//�����u���b�N�ɓ������Ă�����i�n�ʂ����ɓ������Ă���j
    {
        location.y = roundf(location.y);//���W�𐮐��l�ɂ���
        while (stage->HitBlock(this))location.y -= (speed.y / fabsf(speed.y));//�u���b�N�ɓ������Ă���ԁA�i�s�����Ƃ͋t�ɐi�߂�

        if (speed.y > 0.0f)//�n�ʂɓ������Ă���
        {
            is_jump = false;//�W�����v��Ԃ�false�ɂ���
            if (Key::KeyDown(KEY_TYPE::A))speed.y = -JUMP_SPEED;//A�{�^���ŃW�����v
            else speed.y = 0.0f;//A�{�^����������ĂȂ����y���W�̃X�s�[�h��0�ɂ���
        }
        else//���Ƀu���b�N���������Ă���
        {
            speed.y = 0.0f;//Y�̃X�s�[�h��0�ɂ���B
        }
    }
    else is_jump = true;//�u���b�N�ɓ������Ă��Ȃ��Ƃ��i�󒆂ɂ���Ƃ��j�W�����v�ɂ���

}

void Player::Draw() const
{
    DrawBox(location.x - radius.x, location.y - radius.y, location.x + radius.x, location.y + radius.y, 0xffffff, TRUE);
}