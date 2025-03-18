#include "Enemy.hpp"

#include <cmath>
#include <iostream>
#include <random> // 包含亂數生成的標頭文件

#include "Util/Time.hpp"
#include "Util/Transform.hpp"
#include "Util/Input.hpp"

#include "config.hpp"

// Enemy::~Enemy() {
//     // 解構元的具體實現
// }

// void Enemy::Start() {
//     // 初始化敵人的位置
//     pos = {100, 100};

//     // // 初始化敵人的大小
//     // scale = {0.5f, 0.5f};

//     // // 初始化敵人的旋轉角度
//     // rotation = 0.0f;

//     dir = randomMove('z'); // 長頸鹿的移動方向
// }

// void Enemy::Start(glm::vec2 coordinate) {
//     // 初始化敵人的位置
//     pos = coordinate;
//     dir = randomMove('z'); // 長頸鹿的移動方向

//     // 初始化敵人的大小
//     scale = {0.2f, 0.2f};
// }

// void Enemy::Update() {
//     if (m_Visible == false){
//         return;
//     }
//     // 輸出新的位置
//     // std::cout << "Enemy position: (" << pos.x << ", " << pos.y << ")" << std::endl;

//     // 確保敵人不會超出視窗範圍
//     if (pos.y >= (static_cast<float>(PTSD_Config::WINDOW_HEIGHT) - 30) / 2) {
//         // dir.y == randomMove('Y').y;
//         // std::cout << static_cast<float>(PTSD_Config::WINDOW_HEIGHT) << std::endl;
//         dir.y = -dir.y;
//     }
//     else if (pos.y + (static_cast<float>(PTSD_Config::WINDOW_HEIGHT) - 60) / 2 <= 0) {
//         // dir.y == randomMove('y').y;
//         // std::cout << static_cast<float>(PTSD_Config::WINDOW_HEIGHT) << std::endl;

//         dir.y = -dir.y;
//     }
//     if (pos.x >= (static_cast<float>(PTSD_Config::WINDOW_WIDTH) - 480) / 2) {
//         // dir.x == randomMove('X').x;
//         // std::cout << static_cast<float>(PTSD_Config::WINDOW_WIDTH) << std::endl;
//         dir.x = -dir.x;
//     }
//     else if (pos.x + (static_cast<float>(PTSD_Config::WINDOW_WIDTH) - 120)/ 2 <= 0) {
//         // dir.x == randomMove('x').x;
//         dir.x = -dir.x;
//     }

//     // 更新敵人的位置
//     pos += dir *8.0f;
//     // pos += dir * 0.0f;
// }

// glm::vec2 Enemy::coordinate() {
//     return pos;
// }

// bool Enemy::getVisible() const {
//     return m_Visible;
// }

// int Enemy::getHP() const {
//     return m_HP;
// }

// void Enemy::setHP(int hp) {
//     m_HP += hp;
// }

void Enemy::setWall(std::shared_ptr<Wall> wall) {
    m_wall = wall;
}

void Enemy::setGiraffe(glm::vec2 giraffe_pos) {
    Giraffe_pos = giraffe_pos;
}

glm::vec2 Enemy::randomMove(char x) {
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
    // 根據輸入的參數 x 生成移動方向
    switch (x) {
        case 'X': // 右邊界
            return {-std::abs(deltaX), 0}; // 向左移動
        case 'x': // 左邊界
            return {std::abs(deltaX), 0}; // 向右移動
        case 'Y': // 上邊界
            return {0, -std::abs(deltaY)}; // 向下移動
        case 'y': // 下邊界
            return {0, std::abs(deltaY)}; // 向上移動
        default: // 隨機移動
            return {deltaX, deltaY};
    }
}
