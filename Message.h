#pragma once

#include <string>
#include <vector>

class Message
{
private:
    std::vector<std::string> text_line;//メッセージ1桁

    int font;//フォントの種類

    float draw_text_time;//1文字表示するための時間

    int draw_line_text_num;//現在表示できる文字数
    int update_line_text_num;//更新中のメッセージ桁の文字数

    int draw_start_text_line;//表示するメッセージ桁の最初
    int update_text_line;//更新中のメッセージ桁

    bool draw_arrow;//矢印を表示するか？

    int GetLineTextNum(int draw_text_line)const;//指定した桁の文字数を数える
    void UpdateTextLine();//表示中のメッセージ桁の更新

public:
    Message(const char* text_data_name);
    ~Message();

    bool Update(float delta_time);
    void Draw() const;
};
