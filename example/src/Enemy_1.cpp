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

    move_speed = 8.0f;
    
}

void Enemy_1::Update() {
    if (m_Visible == false){
        return;
    }
    // 輸出新的位置
    // std::cout << "Enemy position: (" << pos.x << ", " << pos.y << ")" << std::endl;

    // 確保敵人不會超出視窗範圍
    if ((m_wall->boundary_collision_check_leftright(pos + dir * move_speed) == "right") || m_wall->boundary_collision_check_leftright(pos + dir * move_speed) == "lr") {
        dir.x = - dir.x;
    }
    else if (m_wall->boundary_collision_check_leftright(pos + dir * move_speed) == "left") {
        dir.x = - dir.x;
    }
    if ((m_wall->boundary_collision_check_updown(pos + dir * move_speed) == "up") || m_wall->boundary_collision_check_updown(pos + dir * move_speed) == "ud") {
        dir.y = - dir.y;
    }
    else if (m_wall->boundary_collision_check_updown(pos + dir * move_speed) == "down") {
        dir.y = - dir.y;
    }

    // 更新敵人的位置
    pos += dir * move_speed;
    
    // pos += dir * 0.0f;
}

glm::vec2 Enemy_1::move() {
    return dir;
}

void Enemy_1::shoot() {

}