#include "Boss.hpp"


void Boss_1_1::Start(glm::vec2 coordinate) {
    this->SetDrawable(
        std::make_shared<Util::Image>("../assets/sprites/enemy.png"));
    this->SetZIndex(5);

    final_wish = "Add two Boss_1_2";
    name = "Boss_1_1";

    dir = randomMove('z'); // 長頸鹿的移動方向

    pos = coordinate;
    scale = {0.2f, 0.2f};

    move_speed = 6.0f;
    enemy_hp_start();
}

void Boss_1_1::Update() {
    // std::cout << "Boss_1_1 running" << std::endl;
    if (m_Visible == false){
        return;
    }

    is_burning();

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
    pos += dir * move_speed;
    
    enemy_hp_update();
    // std::cout << "Boss_1_1 updatefinisd" << std::endl;

}

glm::vec2 Boss_1_1::move() {
    return dir;
}

void Boss_1_1::shoot() {

}