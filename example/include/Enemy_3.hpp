#pragma once

#include <cmath>
#include <vector>
#include <memory>

#include "Enemy.hpp"
#include "Wall.hpp"
#include "EnemyArrow.hpp"

class Enemy_3 : public Enemy , public std::enable_shared_from_this<Enemy> {
public:
    Enemy_3() = default;
    ~Enemy_3() override = default;

    void Update() override;
    void Start() override;
    void Start(glm::vec2 coordinate) override;

    glm::vec2 move() override;
    void shoot() override;

    std::vector<std::shared_ptr<EnemyArrow>> m_Arrows; // 射出的箭
private:

    float attect_interval = 0.0f; // 攻擊間隔
};