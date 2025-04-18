#pragma once

#include <glm/fwd.hpp>
#include <memory>
#include <string>
#include <iostream>
#include <vector>

#include "pch.hpp" // IWYU pragma: export
#include "Util/GameObject.hpp"
#include "Util/Text.hpp"

#include "log_my.hpp"
#include "Giraffe.hpp"

class exp_pic_background;
class Giraffe;
class Dark_pic; // 前向宣告
class exp_pic : public Util::GameObject {
public:
    exp_pic() = default;
    ~exp_pic() override = default;

    void Start();
    void Update();

    void setpos(glm::vec2 position); 
    void set_maxexp(int max_exp); 
    void set_maxexp(std::vector<int> max_exp_list); 

    void add_exp(int exp);
    void setpic(int exp);
    int getEXP() const; 
private:

    float exp_scale = 1.0f;
    int exp = 0; // 當前經驗值
    std::vector<int> max_exp_list ; // 經驗值列表>
    int max_exp_iterator = 0; // 當前經驗值列表的索引
    glm::vec2 center ; //校正用

    glm::vec2 &pos = m_Transform.translation; // 位置
    glm::vec2 &scale = m_Transform.scale; // 縮放比例

    std::shared_ptr<exp_pic_background> m_Background; // 用於顯示經驗條的背景
    std::shared_ptr<Dark_pic> m_Dark_pic = std::make_shared<Dark_pic>(); // 用於顯示黑色遮罩
    // std::shared_ptr<Util::Text> m_Text; // 用於顯示血量的文本
};

class exp_pic_background : public Util::GameObject {
public:
    exp_pic_background() = default;
    ~exp_pic_background() override = default;

    void Start();
    void setpos(glm::vec2 position);
private:

    glm::vec2 &pos = m_Transform.translation; // 位置
    glm::vec2 &scale = m_Transform.scale; // 縮放比例

};

class exp_pic_text : public Util::GameObject {
public:
    exp_pic_text() = default;
    ~exp_pic_text() override = default;

    void Start();
    void setpos(glm::vec2 position);
private:
    glm::vec2 &pos = m_Transform.translation; // 位置
    glm::vec2 &scale = m_Transform.scale; // 縮放比例

    int level = 1; // 等級
    std::shared_ptr<Util::Text> m_Text; // 用於顯示血量的文本
};