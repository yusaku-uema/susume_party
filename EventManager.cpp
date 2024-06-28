#include"DxLib.h"
#include"EventManager.h"
#include"PlayerManager.h"

EventManager::EventManager() 
{
    OutputDebugString("EventManagerコンストラクタ呼ばれました。\n");
}

EventManager::~EventManager()
{
    OutputDebugString("EventManagerデストラクタが呼ばれました。\n");
}

void EventManager::Initialize(class Stage* stage, class PlayerManager* player_manager, class EnemyManager* enemy_manager)
{
    this->stage = stage;
    this->player_manager = player_manager;
    this->enemy_manager = enemy_manager;

    EventInitialize(EVENT_TYPE::FIRST_CONVERSATION);
}

void EventManager::EventInitialize(EVENT_TYPE event_type)
{
    this->event_type = event_type;

    if (event_type == EVENT_TYPE::FIRST_CONVERSATION)
    {
        //player_manager->SetMessage("txt/comment.txt");
        player_manager->SetPartyState(true);
    }
}

void EventManager::Update(float delta_time)
{
    if (event_type == EVENT_TYPE::FIRST_CONVERSATION)
    {
        if (!player_manager->GetiIsTalking())
        {
            player_manager->SetPartyState(true);
            EventInitialize(EVENT_TYPE::NONE);
        }
    }
}