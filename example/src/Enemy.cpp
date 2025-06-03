#include "Enemy.hpp"

#include <cmath>
#include <iostream>
#include <random> // 包含亂數生成的標頭文件

#include "Util/Time.hpp"
#include "Util/Transform.hpp"
#include "Util/Input.hpp"

#include "config.hpp"

glm::vec2 Enemy::coordinate() {
    return pos;
}

void Enemy::setWall(std::shared_ptr<Wall> wall) {
    m_wall = wall;
}

void Enemy::setGiraffe(glm::vec2 giraffe_pos) {
    Giraffe_pos = giraffe_pos;
}

void Enemy::setGiraffe(std::shared_ptr<Giraffe> giraffe) {
    m_Giraffe = giraffe;
}

void Enemy::setName(std::string name) {
    this->name = name;
}

std::string Enemy::getName() const {
    return name;
}

std::string Enemy::getFinal_wish() const {
    return final_wish;
}

bool Enemy::getVisible() const {
    return m_Visible;
}

int Enemy::getHP() const {
    return m_HP;
}

void Enemy::setHP(int hp) {
    m_HP += hp;
}

void Enemy::setAtk(int atk) {
    m_atk = atk;
}

int Enemy::getAtk() const {
    return m_atk;
}

void Enemy::setExp_supply(int exp) {
    exp_supply = exp;
}

int Enemy::getExp_supply() const {
    return exp_supply;
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

void Enemy::is_burning() {
    // 判斷是否燃燒
    if (burning and burning_clock >= 2) {
        m_HP -= 1; // 每次更新減少1點血量
        burning_clock = 0; // 重置燃燒計時器
    }
    else {
        burning_clock++; // 增加燃燒計時器
    }
}

void Enemy::enemy_hp_start() {
    // 初始化血量
    m_hp_pic->Start(pos);
    m_hp_pic->set_maxhp(m_HP);
    this->AddChild(m_hp_pic);
}

void Enemy::enemy_hp_update() {
    // 更新血量
    m_hp_pic->setpic(m_HP);
    m_hp_pic->Update(pos);
}
