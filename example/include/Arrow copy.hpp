#ifndef ARROW_HPP
#define ARROW_HPP

#include "pch.hpp" // IWYU pragma: export
#include "Util/GameObject.hpp"

class Arrow : public Util::GameObject {
public:
    // Arrow() = default;
    // ~Arrow() override; // 在 .hpp 文件中聲明解構元
    Arrow(glm::vec2 &player_coordinate, glm::vec2 &enemy_coordinate);
    // Arrow(const glm::vec2 &arrowPosition, const glm::vec2 &arrowDirection); //

    void Update();
    void Start();
    glm::vec2 coordinate();

private:
    glm::vec2 &pos = m_Transform.translation; // 箭的位置
    glm::vec2 &scale = m_Transform.scale; // 箭的大小
    float &rotation = m_Transform.rotation; // 箭的旋轉角度

    glm::vec2 m_EnemyCoordinate; // 敵人的位置
    glm::vec2 m_PlayerCoordinate; // 玩家的位置

    glm::vec2 arrowPosition; // 箭的位置
    glm::vec2 arrowDirection; // 箭的方向
    glm::vec2 m_Direction; // 箭的方向
};





#endif // ARROW_HPP