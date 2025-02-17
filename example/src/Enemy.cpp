#include "Enemy.hpp"

#include <cmath>
#include <iostream>
#include <random> // 包含亂數生成的標頭文件

#include "Util/Time.hpp"
#include "Util/Transform.hpp"
#include "Util/Input.hpp"

#include "config.hpp"

Enemy::~Enemy() {
    // 解構元的具體實現
}

void Enemy::Update() {
    
    // 更新敵人的位置
    auto dir = randomMove(); // 長頸鹿的移動方向
    pos += dir *16.0f;
    // pos += dir * 0.0f;

    // 輸出新的位置
    // std::cout << "Enemy position: (" << pos.x << ", " << pos.y << ")" << std::endl;
}

glm::vec2 Enemy::coordinate() {
    return pos;
}

glm::vec2 Enemy::randomMove() {
    // 創建亂數生成器
    std::random_device rd;
    std::mt19937 gen(rd()); // 以隨機設備為種子
    std::uniform_real_distribution<float> dis(-1.0f, 1.0f); // 生成範圍為 -1 到 1 的均勻分佈

    // 生成亂數移動幅度
    float deltaX = dis(gen);
    float deltaY = dis(gen);

    // 確保移動幅度不大於 1
    if (std::abs(deltaX) > 1.0f) {
        deltaX = (deltaX > 0 ? 1.0f : -1.0f);
    }
    if (std::abs(deltaY) > 1.0f) {
        deltaY = (deltaY > 0 ? 1.0f : -1.0f);
    }

    return {deltaX, deltaY};
}