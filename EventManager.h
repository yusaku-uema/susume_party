#pragma once

class EventManager
{
private:
    enum class EVENT_TYPE
    {
        FIRST_CONVERSATION,//最初の会話（王様）
        NONE,//イベントなし
    };

    class Stage* stage;
    class PlayerManager* player_manager;
    class EnemyManager* enemy_manager;

    EVENT_TYPE event_type;

public:
    EventManager();
    ~EventManager();

    void Initialize(class Stage* stage, class PlayerManager* player_manager, class EnemyManager* enemy_manager);
    void EventInitialize(EVENT_TYPE event_type);//イベントごとの初期化

    void Update(float delta_time);
};