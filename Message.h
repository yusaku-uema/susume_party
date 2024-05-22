#pragma once

#include <string>
#include <vector>

class Message
{
private:
    std::vector<std::string> text_line;//���b�Z�[�W1�s

    int font;//�t�H���g�̎��
    float draw_text_time;//1�����\�����邽�߂̎���
    int draw_text_count;//���ݕ\���ł��镶����

public:
    Message(const char* text_data_name);
    ~Message();
    
    bool Update(float delta_time);
    void Draw() const;
};
