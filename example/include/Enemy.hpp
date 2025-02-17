#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "pch.hpp" // IWYU pragma: export
#include "Util/GameObject.hpp"

class Enemy : public Util::GameObject {
public:
    Enemy() = default;
    ~Enemy() override; // 在 .hpp 文件中聲明解構元
    void Update();
    void Start();
    glm::vec2 coordinate();

private:
    glm::vec2 &pos = m_Transform.translation; // 敵人的位置
    glm::vec2 &scale = m_Transform.scale; // 敵人的大小
    float &rotation = m_Transform.rotation; // 敵人的旋轉角度

    glm::vec2 randomMove();
};











#endif // ENEMY_HPP