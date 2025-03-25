#include "Enemy_3.hpp"
#include "config.hpp"
#include "Util/Time.hpp"


#include <iostream>
#include <memory>


// 會射射的敵人

void Enemy_3::Start() {
    pos = {100, 100};

    scale = {0.2f, 0.2f};
}
void Enemy_3::Start(glm::vec2 coordinate) {
    pos = coordinate;
    scale = {0.2f, 0.2f};
    move_speed = 0.0f;
}

void Enemy_3::Update() {
    if (m_Visible == false){
        for (auto it = m_Arrows.begin(); it != m_Arrows.end();) {
            this->RemoveChild(*it);
            it = m_Arrows.erase(it); // 刪除箭
        }
        return;
    }

    attect_interval += static_cast<float>(Util::Time::GetDeltaTimeMs()) / 16.0f;
    if (attect_interval >= 100.0f) {
        shoot();
        attect_interval = 0.0f;
    }
    for (auto it = m_Arrows.begin(); it != m_Arrows.end();) {
        (*it)->setTarget(m_Giraffe);
        (*it)->Update();
        if ((*it)->shouldDelete()) {
            this->RemoveChild(*it);
            it = m_Arrows.erase(it); // 刪除箭
            // std::cout << "Arrow deleted" << std::endl;
        } else {
            ++it;
        }
    
    }
}

glm::vec2 Enemy_3::move() {
    return dir;
}

void Enemy_3 ::shoot() {

    glm::vec2 toGiraffe = m_Giraffe->coordinate() - pos;
    // 計算敵人到長頸鹿的距離


    // 生成一個子彈
    std::shared_ptr<EnemyArrow> m_arrow = std::make_shared<EnemyArrow>();

    m_arrow->setTarget(shared_from_this());
    m_arrow->setTarget(m_Giraffe);
    m_arrow->setWall(m_wall);

    m_arrow->Start();
    m_Arrows.push_back(m_arrow); // 將箭存儲到向量中
    this->AddChild(m_arrow);
    // // 設置子彈的位置
    // arrow->Start(pos);
    // // 設置子彈的方向
    // arrow->setDirection(dir);
}