#include "Boss.hpp"

void Boss_1_4::Start(glm::vec2 coordinate) {
    this->SetDrawable(
        std::make_shared<Util::Image>("../assets/sprites/enemy.png"));
    this->SetZIndex(5);
        
    final_wish = "Add player's hp";
    name = "Boss_1_4";

    dir = randomMove('z'); // 長頸鹿的移動方向

    pos = coordinate;
    scale = {0.2f, 0.2f};

    move_speed = 12.0f;
    enemy_hp_start();
}

void Boss_1_4::Update() {
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
}

glm::vec2 Boss_1_4::move() {
    return dir;
}

void Boss_1_4::shoot() {

}