#pragma once

class EventManager
{
private:
    enum class EVENT_TYPE
    {
        FIRST_CONVERSATION,//�ŏ��̉�b�i���l�j
        NONE,//�C�x���g�Ȃ�
    };

    class Stage* stage;
    class PlayerManager* player_manager;
    class EnemyManager* enemy_manager;

    EVENT_TYPE event_type;

public:
    EventManager();
    ~EventManager();

    void Initialize(class Stage* stage, class PlayerManager* player_manager, class EnemyManager* enemy_manager);
    void EventInitialize(EVENT_TYPE event_type);//�C�x���g���Ƃ̏�����

    void Update(float delta_time);
};