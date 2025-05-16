#pragma once

#include <cmath>
#include <vector>
#include <memory>

#include "Enemy.hpp"
#include "Wall.hpp"
#include "EnemyArrow.hpp"

class Enemy_4 : public Enemy , public std::enable_shared_from_this<Enemy> {
public:
    Enemy_4() = default;
    ~Enemy_4() override = default;

    void Start(glm::vec2 coordinate) override;
    void Update() override;

    glm::vec2 move() override;
    void shoot() override;

private:
    int atk_speed = 360;
    int count = 0; // 計數器
    bool decide_dir = false; // 判斷是否要改變方向

    std::vector<std::shared_ptr<EnemyArrow>> m_stones; // 射出的箭
    void stone_shoot(std::shared_ptr<EnemyArrow> m_stone , glm::vec2 direction = glm::vec2(0.0f,0.0f)); // 射石頭
    int rotation_count = 0; // 計數器
    // void rotation_attack(); // 旋轉

    bool bool_logger = false;
};  