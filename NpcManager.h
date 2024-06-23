#pragma once
#include <vector>
#include"NpcBase.h"

class NpcManager
{
private:
    class Stage* stage;
    class PlayerManager* player_manager;
    std::vector<class NpcBase*>npc;

    int event_image[2];//�I�}�[�N�A�C�R��

    char text_data_name[256];//��b�̃f�[�^��
    bool can_conversation;//��b�ł��邩�H
    int can_conversation_npc_num;//��b�\�L����

public:

    NpcManager();
    ~NpcManager();

    void Update(float delta_time);
    void Draw() const;

    void Initialize(class Stage* stage, class PlayerManager* player_manager);


};