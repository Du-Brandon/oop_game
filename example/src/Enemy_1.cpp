#include "Enemy_1.hpp"

#include "App.hpp" 
#include "config.hpp"
#include <iostream>

void Enemy_1::Start(glm::vec2 coordinate) {
    this->SetDrawable(
    std::make_shared<Util::Image>("../assets/sprites/enemy.png"));
    this->SetZIndex(5);
    // 初始化敵人的位置
    pos = coordinate;
    dir = randomMove('z'); // 長頸鹿的移動方向

    // 初始化敵人的大小
    scale = {0.2f, 0.2f};

    move_speed = 6.0f;
    
    enemy_hp_start();
}

void Enemy_1::Update() {
    if (m_Visible == false){
        return;
    }

    is_burning();
    
    // 輸出新的位置
    // std::cout << "Enemy position: (" << pos.x << ", " << pos.y << ")" << std::endl;

    static bool decide_dir = false; // 用於決定是否隨機生成移動方向

    // 確保敵人不會超出視窗範圍
    if (m_wall->boundary_collision_check_updown(pos + dir * move_speed) == "ud" or m_wall->boundary_collision_check_updown(pos + dir * move_speed) == "lr") {
        // 重新隨機生成移動方向
        dir = randomMove('z');
        decide_dir = true;
    }
    else {
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
    }
    // 更新敵人的位置
    if (!decide_dir){ 
        pos += dir * move_speed;
    }
    decide_dir = false; // 重置決定方向的標誌
    enemy_hp_update();
}

glm::vec2 Enemy_1::move() {
    return dir;
}

void Enemy_1::shoot() {

}