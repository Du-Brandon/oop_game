#pragma once

#include <Util/GameObject.hpp>
#include <cmath>
#include <vector>
#include <memory>

#include "Enemy.hpp"
#include "Enemy_7.hpp"
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
    bool decide_dir = false; // 判斷是否要改變方向

    void stuck_move(); // 用來卡住敵人

};

