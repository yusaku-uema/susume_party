#include"DxLib.h"
#include"Ui.h"

Ui::Ui(PlayerBase** player_base) : player(player_base)
{
    if (LoadDivGraph("image/Ui/player.png", 4, 4, 1, 50, 50, player_image[0]) == -1)throw("image/Ui/player.pngが読み込めません\n");
    if (LoadDivGraph("image/Ui/playerselect.png", 4, 4, 1, 50, 50, player_image[1]) == -1)throw("image/Ui/playerselect.pngが読み込めません\n");
    if (LoadDivGraph("image/Ui/playerdead.png", 4, 4, 1, 50, 50, player_image[2]) == -1)throw("image/Ui/playerdead.pngが読み込めません\n");

    SetFontSize(10);

    OutputDebugString("Uiコンストラクタ呼ばれました。\n");
}

Ui::~Ui()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)DeleteGraph(player_image[i][j]);
    }

    OutputDebugString("Uiデストラクタが呼ばれました。\n");
}

void Ui::Update()
{
    for (int i = 0; i < 4; i++)
    {
        int player_job = static_cast<int>(player[i]->GetPlayerJob());

        draw_player_state[player_job].hp = player[i]->GetHp();
        draw_player_state[player_job].mp = player[i]->GetMp();

        draw_player_state[player_job].image_type = 0;
        if (player[i]->GetIsLeader())draw_player_state[player_job].image_type = 1;
        if (player[i]->GetIsDead())draw_player_state[player_job].image_type = 2;
    }
}

void Ui::Draw() const
{
    for (int i = 3; i >= 0; i--)
    {
        DrawBox(i * 320, 540, (i + 1) * 320, 720, 0x000000, TRUE);
       
        DrawRotaGraph(i * 320 + 20, 650, 3.5, 0, player_image[draw_player_state[i].image_type][i], TRUE);

        int frame_color = 0xffffff;
        if (draw_player_state[i].image_type == 1)frame_color = 0xff0000;

        DrawBox(i * 320, 540, (i + 1) * 320, 720, frame_color, FALSE);

        DrawFormatString((i * 320) + 100, 600, 0xffffff, "HP = %3d", draw_player_state[i].hp);
        DrawFormatString((i * 320) + 100, 630, 0xffffff, "MP = %3d", draw_player_state[i].mp);
    }
}