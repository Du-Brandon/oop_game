#pragma once

#include <cmath>
#include <vector>
#include <memory>

#include "Enemy.hpp"
#include "Wall.hpp"
#include "EnemyArrow.hpp"

class Enemy_6 : public Enemy , public std::enable_shared_from_this<Enemy> {
public:
    Enemy_6() = default;
    ~Enemy_6() override = default;

    void Update() override;
    void Start(glm::vec2 coordinate) override;

    glm::vec2 move() override;
    void shoot() override;
private:
    int atk_speed = 300;
    int count = 0; // 計數器
    bool decide_dir = false; // 判斷是否要改變方向
    
    std::vector<std::shared_ptr<EnemyArrow>> m_Arrows; // 射出的箭

    float attect_interval = 0.0f; // 攻擊間隔
};