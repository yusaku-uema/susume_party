#include"DxLib.h"
#include"PlayerBase.h"
#include"Key.h"

#define PLAYER_SIZE 30.0f//�T�C�Y
#define WALK_SPEED 2.0f//1�t���[���Ői�ޑ���
#define JUMP_SPEED 8.0f//1�t���[���ŃW�����v���鍂��
#define ACCELERATION 0.3f//�������̉���
#define CHARACTER_DISTANCE 50.0f//�L�����N�^�[���m�̋���

PlayerBase::PlayerBase() : CharacterBase({ 90.0f, 200.0f }, { PLAYER_SIZE, PLAYER_SIZE }, 20, 10, 5, 5)
{
    for (int i = 0; i < JUMP_LOG; i++)jump_log[i] = false;
    OutputDebugString("PlayerBase�R���X�g���N�^�Ă΂�܂����B\n");
}

PlayerBase::~PlayerBase()
{
    OutputDebugString("PlayerBase�f�X�g���N�^���Ă΂�܂����B\n");
}

void PlayerBase::Update(float delta_time, class Stage* stage, CharacterBase* character)
{
    //x���W�̍X�V
    MoveX(stage, character);
    location.x += speed.x;
    if (stage->HitBlock(this))//�u���b�N�ɓ������Ă���ꍇ�A���W�𒲐�
    {
        location.x = roundf(location.x);//���W�𐮐��l�ɂ���
        while (stage->HitBlock(this))location.x -= (speed.x / fabsf(speed.x));//�u���b�N�ɓ������Ă���ԁA�i�s�����Ƃ͋t�ɐi�߂�
    }

    //y���W�̍X�V
    if ((speed.y += GRAVITY) > FALL_SPEED)speed.y = FALL_SPEED;//�d�͂���萔���z���Ȃ��悤�ɂ���
    location.y += speed.y;//���W�̉��Z
    MoveY(stage, character);
}

void PlayerBase::MoveX(class Stage* stage, CharacterBase* character)
{
    if (character == nullptr)
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
        if ((character->GetLocation().x > location.x) && ((character->GetLocation().x - location.x) > CHARACTER_DISTANCE))
        {
            if ((speed.x += ACCELERATION) > WALK_SPEED)speed.x = WALK_SPEED;
        }
        else if ((character->GetLocation().x < location.x) && ((location.x - character->GetLocation().x) > CHARACTER_DISTANCE))
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

void PlayerBase::MoveY(class Stage* stage, CharacterBase* character)
{
    if (stage->HitBlock(this))//�����u���b�N�ɓ������Ă�����i�n�ʂ����ɓ������Ă���j
    {
        location.y = roundf(location.y);//���W�𐮐��l�ɂ���
        while (stage->HitBlock(this))location.y -= (speed.y / fabsf(speed.y));//�u���b�N�ɓ������Ă���ԁA�i�s�����Ƃ͋t�ɐi�߂�

        if (speed.y > 0.0f)//�n�ʂɓ������Ă���ꍇ
        {
            if (character == nullptr && Key::KeyDown(KEY_TYPE::A))
            {
                speed.y = -JUMP_SPEED;//A�{�^���ŃW�����v

            }
            else speed.y = 0.0f;//A�{�^����������ĂȂ����Y�̃X�s�[�h��0�ɂ���
        }
        else speed.y = 0.0f;//���Ƀu���b�N���������Ă���ꍇ�AY�̃X�s�[�h��0�ɂ���
    }
}

void PlayerBase::Draw() const
{
    DrawBox(location.x - radius.x, location.y - radius.y, location.x + radius.x, location.y + radius.y, 0xffffff, TRUE);
}