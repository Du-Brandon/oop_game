#pragma once

#include <glm/fwd.hpp>
#include <string>
#include <iostream>
#include <vector>

#include "pch.hpp" // IWYU pragma: export
#include "Util/GameObject.hpp"

class Ground_Spikes : public Util::GameObject {
public:

    void Start(glm::vec2 pos); // 添加這個方法來建立尖刺的坐標
    glm::vec2 coordinate() { return pos; } // 返回尖刺的坐標

private:
    glm::vec2 &pos = m_Transform.translation; // 尖刺的位置
    glm::vec2 &scale = m_Transform.scale; // 尖刺的大小
    
};

class Vecter_Ground_Spikes : public Util::GameObject {
public:

    void Start(); // 添加這個方法來建立尖刺的坐標
    void Add_Spikes(glm::vec2 pos); // 添加尖刺的坐標
    bool collision_check(glm::vec2 coordinate); // 判斷是否碰撞
    void clear(); // 清除尖刺的坐標

private:
    std::vector<std::shared_ptr<Ground_Spikes>> m_Ground_Spikes; // 尖刺的坐標
};