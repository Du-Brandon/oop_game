#include "Enemy_1.hpp"

#include "App.hpp"
#include "config.hpp"
#include <iostream>

void Enemy_1::Start() {
    // 初始化敵人的位置
    pos = {100, 100};

    // // 初始化敵人的大小
    // scale = {0.5f, 0.5f};

    // // 初始化敵人的旋轉角度
    // rotation = 0.0f;

    dir = randomMove('z'); // 長頸鹿的移動方向
}

void Enemy_1::Start(glm::vec2 coordinate) {
    // 初始化敵人的位置
    pos = coordinate;
    dir = randomMove('z'); // 長頸鹿的移動方向

    // 初始化敵人的大小
    scale = {0.2f, 0.2f};
}

void Enemy_1::Update() {
    if (m_Visible == false){
        return;
    }
    // 輸出新的位置
    // std::cout << "Enemy position: (" << pos.x << ", " << pos.y << ")" << std::endl;

    // 確保敵人不會超出視窗範圍
    if (pos.y >= (static_cast<float>(PTSD_Config::WINDOW_HEIGHT) - 30) / 2) {
        // dir.y == randomMove('Y').y;
        // std::cout << static_cast<float>(PTSD_Config::WINDOW_HEIGHT) << std::endl;
        dir.y = -dir.y;
    }
    else if (pos.y + (static_cast<float>(PTSD_Config::WINDOW_HEIGHT) - 60) / 2 <= 0) {
        // dir.y == randomMove('y').y;
        // std::cout << static_cast<float>(PTSD_Config::WINDOW_HEIGHT) << std::endl;

        dir.y = -dir.y;
    }
    if (pos.x >= (static_cast<float>(PTSD_Config::WINDOW_WIDTH) - 480) / 2) {
        // dir.x == randomMove('X').x;
        // std::cout << static_cast<float>(PTSD_Config::WINDOW_WIDTH) << std::endl;
        dir.x = -dir.x;
    }
    else if (pos.x + (static_cast<float>(PTSD_Config::WINDOW_WIDTH) - 120)/ 2 <= 0) {
        // dir.x == randomMove('x').x;
        dir.x = -dir.x;
    }

    // 更新敵人的位置
    pos += dir *8.0f;
    // pos += dir * 0.0f;
}

glm::vec2 Enemy_1::coordinate() const {
    return pos;
}

void Enemy_1::move() {

}

void Enemy_1::shoot() {

}

int Enemy_1::getHP() const {
    return m_HP;
}

void Enemy_1::setHP(int hp) {
    m_HP += hp;
}

void Enemy_1::setAtk(int atk) {
    m_atk = atk;
}

int Enemy_1::getAtk() const {
    return m_atk;
}

void Enemy_1::setExp_supply(int exp) {
    exp_supply = exp;
}

int Enemy_1::getExp_supply() const {
    return exp_supply;
}

bool Enemy_1::getVisible() const {
    return m_Visible;
}