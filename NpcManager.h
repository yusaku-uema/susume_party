#pragma once
#include <vector>
#include"NpcBase.h"

class NpcManager
{
private:
    class Stage* stage;
    class PlayerManager* player_manager;
    std::vector<class NpcBase*>npc;

    int event_image[2];//！マークアイコン

    char text_data_name[256];//会話のデータ名
    bool can_conversation;//会話できるか？
    int can_conversation_npc_num;//会話可能キャラ

public:

    NpcManager();
    ~NpcManager();

    void Update(float delta_time);
    void Draw() const;

    void Initialize(class Stage* stage, class PlayerManager* player_manager);


};