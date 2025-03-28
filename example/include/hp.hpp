#pragma once

#include <glm/fwd.hpp>
#include <string>
#include <iostream>
#include <vector>

#include "pch.hpp" // IWYU pragma: export
#include "Util/GameObject.hpp"
#include "Util/Text.hpp"

class hp_pic : public Util::GameObject {
public:
    hp_pic() = default;
    ~hp_pic() override = default;

    void Start(glm::vec2 tp);
    void Update();
    void setpic(int hp); // 添加這個方法來設置長頸鹿的血量
    int getHP() const; // 添加這個方法來獲取血量

private:
    int max_hp = 1000;
    int current_hp = 1000;
    glm::vec2 Target_pos ; // 長頸鹿的位置

    glm::vec2 &pos = m_Transform.translation; // 長頸鹿的位置
    glm::vec2 &scale = m_Transform.scale; // 長頸鹿的縮放比例
    std::shared_ptr<Util::Text> m_Text; // 用於顯示血量的文本


};