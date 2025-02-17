#include "Arrow.hpp"

#include <cmath>
#include <iostream>

#include "pch.hpp" // IWYU pragma: export

#include "Util/Renderer.hpp"
#include "Util/Time.hpp"
#include "Util/Transform.hpp"
#include "Util/Input.hpp"

#include "config.hpp"

Arrow::Arrow(glm::vec2 &player_coordinate, glm::vec2 &enemy_coordinate) : m_PlayerCoordinate(player_coordinate), m_EnemyCoordinate(enemy_coordinate) {
    m_Direction = glm::normalize(enemy_coordinate - player_coordinate);
    // 構造元的具體實現
}
// Arrow::Arrow(const glm::vec2 &arrowPosition, const glm::vec2 &arrowDirection): arrowPosition(arrowPosition), arrowDirection(arrowDirection) {
//     // pos = arrowPosition;
//     // m_Direction = arrowDirection;
//     // 構造元的具體實現
// }

// Arrow::~Arrow() {
//     // 解構元的具體實現
// }

void Arrow::Start(){
    // this -> SetDrawable(std::make_shared<Util::Image>("../assets/sprites/arrow.png"));
    // 初始化箭的位置
    pos = m_PlayerCoordinate;

    // 初始化箭的大小
    scale = {0.05f, 0.05f};
    // 初始化箭的旋轉角度
    rotation = 5.49778f;
}

void Arrow::Update() {
    // 更新箭的位置
    pos += m_Direction * 0.1f; // 假設箭以固定速度移動
    // pos += arrowDirection * 0.1f; // 假設箭以固定速度移動
}

glm::vec2 Arrow::coordinate() {
    return pos;
}