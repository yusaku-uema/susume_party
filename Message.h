#pragma once

#include <string>
#include <vector>

class Message
{
private:
    std::vector<std::string> text_line;//���b�Z�[�W1��

    int font;//�t�H���g�̎��

    float draw_text_time;//1�����\�����邽�߂̎���

    int draw_line_text_num;//���ݕ\���ł��镶����
    int update_line_text_num;//�X�V���̃��b�Z�[�W���̕�����

    int draw_start_text_line;//�\�����郁�b�Z�[�W���̍ŏ�
    int update_text_line;//�X�V���̃��b�Z�[�W��
    bool can_update_text_line;//���b�Z�[�W�����X�V�ł��邩�H

    int GetLineTextNum(int draw_text_line)const;//�w�肵�����̕������𐔂���
    void UpdateTextLine();//�\�����̃��b�Z�[�W���̍X�V

public:
    Message(const char* text_data_name);
    ~Message();
    
    bool Update(float delta_time);
    void Draw() const;
};
