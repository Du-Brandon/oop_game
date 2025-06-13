# include "Enemy_2.hpp"
# include "config.hpp"
# include <iostream>

void Enemy_2::Start(glm::vec2 coordinate) {
    this->SetDrawable(
        std::make_shared<Util::Image>("../assets/sprites/enemy2.png"));
    this->SetZIndex(5);

    pos = coordinate;
    scale = {0.2f, 0.2f};
    this->setHP(100);
    move_speed = 2.0f;

    enemy_hp_start();
}

void Enemy_2::Update(){
    dir = move();
    
    if (m_Visible == false){
        return;
    }

    is_burning();

    if ((m_wall->boundary_collision_check_leftright(pos + dir * move_speed) == "right") ) {
        dir.x = 0;
    }
    else if (m_wall->boundary_collision_check_leftright(pos + dir * move_speed) == "left") {
        dir.x = 0;
    }
    else if (m_wall->boundary_collision_check_leftright(pos + dir * move_speed) == "lr") {
        dir.x = 0;
    }
    if (m_wall->boundary_collision_check_updown(pos + dir * move_speed) == "up") {
        dir.y = 0;
    }
    else if (m_wall->boundary_collision_check_updown(pos + dir * move_speed) == "down") {
        dir.y = 0;
    }
    else if (m_wall->boundary_collision_check_updown(pos + dir * move_speed) == "ud") {
        dir.y = 0;
    }

    pos += dir * move_speed;

    enemy_hp_update();

}

// 追擊giraffe
glm::vec2 Enemy_2::move() {
    // 計算敵人到長頸鹿的向量
    glm::vec2 toGiraffe = m_Giraffe->coordinate() - pos;
    // 計算敵人到長頸鹿的距離
    float distance = glm::length(toGiraffe);
    // 計算敵人到長頸鹿的單位向量
    glm::vec2 dir = toGiraffe / distance;
    
    return dir;
}

void Enemy_2::shoot() {
    // 生成一個子彈
    // std::shared_ptr<Arrow> arrow = std::make_shared<Arrow>();
    // // 設置子彈的位置
    // arrow->Start(pos);
    // // 設置子彈的方向
    // arrow->setDirection(dir);
    // // 將子彈添加到 m_Arrows 中
    // m_Arrows.push_back(arrow);
}



