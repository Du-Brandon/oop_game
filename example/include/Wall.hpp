#pragma once

#include "pch.hpp" // IWYU pragma: export
#include "Util/GameObject.hpp"

class Wall : public Util::GameObject {
public:
    Wall(); // 構造元

    void Start(glm::vec2 coordinate_left_bottom, glm::vec2 coordinate_right_top); 
    void Start(glm::vec2 coordinate_center, float radius);
    void Update();
    void end();

    glm::vec2 coordinate();

    // 添加這個方法來建立牆的坐標
    bool collision_check(glm::vec2 coordinate);

private:
    void set_Square_Coordinate(glm::vec2 coordinate_left_bottom, glm::vec2 coordinate_right_top);
    void set_Circle_Coordinate(glm::vec2 coordinate_center, float radius);
    bool is_circle = false; // 判斷牆是不是圓形

    glm::vec2 &pos = m_Transform.translation; // 牆的位置
    glm::vec2 &scale = m_Transform.scale; // 牆的大小
    float &rotation = m_Transform.rotation; // 牆的旋轉角度
    glm::vec2 left_bottom;
    glm::vec2 right_top;
    glm::vec2 center;
    float radius;
};