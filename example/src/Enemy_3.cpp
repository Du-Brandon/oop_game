#include "Enemy_3.hpp"
#include "config.hpp"
#include "Util/Time.hpp"


#include <iostream>
#include <memory>


// 會射射的敵人

void Enemy_3::Start(glm::vec2 coordinate) {
    this->SetDrawable(
    std::make_shared<Util::Image>("../assets/sprites/enemy3.png"));
    this->SetZIndex(5);

    pos = coordinate;
    scale = {0.2f, 0.2f};
    move_speed = 0.0f;

    m_atk = 10;

    enemy_hp_start();
}

void Enemy_3::Update() {
    if (m_Visible == false){
        for (auto it = m_Arrows.begin(); it != m_Arrows.end();) {
            this->RemoveChild(*it);
            it = m_Arrows.erase(it); // 刪除箭
        }
        return;
    }

    is_burning();

    attect_interval += static_cast<float>(Util::Time::GetDeltaTimeMs()) / 16.0f;
    if (attect_interval >= 100.0f) {
        shoot();
        attect_interval = 0.0f;
    }
    for (auto it = m_Arrows.begin(); it != m_Arrows.end();) {
        (*it)->setTarget(m_Giraffe);
        (*it)->Update(true);
        if ((*it)->shouldDelete()) {
            this->RemoveChild(*it);
            it = m_Arrows.erase(it); // 刪除箭
            // std::cout << "Arrow deleted" << std::endl;
        } else {
            ++it;
        }
    
    }

    enemy_hp_update();
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

    m_arrow->Start("",glm::normalize(m_Giraffe->coordinate() - pos),"arrow");
    m_arrow->Setspeed(4.0f); // 設置子彈速度
    m_Arrows.push_back(m_arrow); // 將箭存儲到向量中
    this->AddChild(m_arrow);
    // // 設置子彈的位置
    // arrow->Start(pos);
    // // 設置子彈的方向
    // arrow->setDirection(dir);
}