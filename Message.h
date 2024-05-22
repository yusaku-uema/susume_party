#pragma once

#include <string>
#include <vector>

class Message
{
private:
    std::vector<std::string> text_line;//メッセージ1行

    int font;//フォントの種類
    float draw_text_time;//1文字表示するための時間
    int draw_text_count;//現在表示できる文字数

public:
    Message(const char* text_data_name);
    ~Message();
    
    bool Update(float delta_time);
    void Draw() const;
};
