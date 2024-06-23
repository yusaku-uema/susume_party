#include"DxLib.h"
#include"NpcManager.h"
#include"PlayerManager.h"
#include"Key.h"

#include"King.h"

//NPCと話せる最大距離
#define MAX_CONVERSATION_DISTANCE 150.0f
//NPCと話せる最小距離
#define MIN_CONVERSATION_DISTANCE 70.0f

NpcManager::NpcManager() : can_conversation(false), can_conversation_npc_num(0)
{
    if (LoadDivGraph("image/Npc/event.png", 2, 2, 1, 16, 16, event_image) == -1)throw("image/Npc/event.pngが読み込めません\n");

    OutputDebugString("NpcManagerコンストラクタ呼ばれました。\n");
}

NpcManager::~NpcManager()
{
    for (int i = 0; i < 2; i++)DeleteGraph(event_image[i]);

    for (int i = 0; i < npc.size(); i++)delete npc[i];

    npc.clear();
    npc.shrink_to_fit();

    OutputDebugString("NpcManagerデストラクタが呼ばれました。\n");
}

void NpcManager::Initialize(class Stage* stage, class PlayerManager* player_manager)
{
    this->stage = stage;
    this->player_manager = player_manager;

    npc.emplace_back(new King(DATA{ 150,400 }, DATA{ 50,50 }, stage, player_manager, "txt/kingcomment.txt"));
}

void NpcManager::Update(float delta_time)
{
    float player_distance = MAX_CONVERSATION_DISTANCE;
    can_conversation = false;

    for (int i = 0; i < npc.size(); i++)
    {
        npc[i]->Update();

        float dx = npc[i]->GetLocation().x - player_manager->GetPlayerData()->GetLocation().x;
        float dy = npc[i]->GetLocation().y - player_manager->GetPlayerData()->GetLocation().y;
        float distance = sqrt(dx * dx + dy * dy); // ユークリッド距離の計算（平方根を取る）

        if ((distance < player_distance)/* && (distance > MIN_CONVERSATION_DISTANCE)*/)
        {
            can_conversation = true;
            strcpy_s(text_data_name, sizeof(text_data_name), npc[i]->GetTextDataName());
            player_distance = distance;
            can_conversation_npc_num = i;
        }
    }

    if ((Key::KeyDown(KEY_TYPE::A)) && (can_conversation))player_manager->SetMessage(text_data_name);
}

void NpcManager::Draw() const
{
    for (int i = 0; i < npc.size(); i++)
    {
        npc[i]->Draw();
    }

    if (can_conversation)
    {
        DrawRotaGraph(npc[can_conversation_npc_num]->GetLocation().x + stage->GetCameraWork(), npc[can_conversation_npc_num]->GetLocation().y - 100, 3, 0, event_image[0], TRUE);
    }
}