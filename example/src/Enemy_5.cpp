#include "Enemy_5.hpp"
#include "log_my.hpp"
#include <cstdlib>

void Enemy_5::Start(glm::vec2 coordinate) {
    pos = coordinate;
    scale = {0.2f, 0.2f};
    move_speed = 0.0f;
    m_HP = 200;
    exp_supply = 15;
    this->SetZIndex(5);
    this->SetDrawable(std::make_shared<Util::Image>("../assets/sprites/enemy.png"));
    
    final_wish = "Add player's hp";
    name = "Enemy_5";

    enemy_hp_start();
}

void Enemy_5::Update() {
    if (m_Visible == false){
        return;
    }

    is_burning();
    
    enemy_hp_update();
}

void Enemy_5::shoot() {
    // 射擊邏輯
}

glm::vec2 Enemy_5::move() {
    return dir;
}