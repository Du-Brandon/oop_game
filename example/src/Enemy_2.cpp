# include "Enemy_2.hpp"
# include "config.hpp"
# include <iostream>

void Enemy_2::Start() {
    pos = {100, 100};

    scale = {0.2f, 0.2f};

}

void Enemy_2::Start(glm::vec2 coordinate) {
    pos = coordinate;
    scale = {0.2f, 0.2f};
    this->setHP(1000);
}

void Enemy_2::Update(){
    dir = move();
    
    if (m_Visible == false){
        return;
    }
    if (pos.y >= (static_cast<float>(PTSD_Config::WINDOW_HEIGHT) - 30) / 2) {
        dir.y = -dir.y;
    }
    else if (pos.y + (static_cast<float>(PTSD_Config::WINDOW_HEIGHT) - 60) / 2 <= 0) {
        dir.y = -dir.y;
    }
    if (pos.x >= (static_cast<float>(PTSD_Config::WINDOW_WIDTH) - 480) / 2) {
        dir.x = -dir.x;
    }
    else if (pos.x + (static_cast<float>(PTSD_Config::WINDOW_WIDTH) - 120)/ 2 <= 0) {
        dir.x = -dir.x;
    }

    pos += dir * 2.0f;

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



