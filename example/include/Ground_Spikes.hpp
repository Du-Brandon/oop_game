#pragma once

#include <glm/fwd.hpp>
#include <string>
#include <iostream>
#include <vector>

#include "pch.hpp" // IWYU pragma: export
#include "Util/GameObject.hpp"

class Ground_Spikes : public Util::GameObject {
public:

    void Start(glm::vec2 pos); // 添加這個方法來建立邊界的坐標
    void Setspikes(glm::vec2 pos); // 設置尖刺的坐標


private:
    glm::vec2 &pos = m_Transform.translation; // 尖刺的位置
    glm::vec2 &scale = m_Transform.scale; // 尖刺的大小
};