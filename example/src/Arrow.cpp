#include "Arrow.hpp"

#include <cmath>
#include <iostream>

#include "Enemy.hpp"
#include "Giraffe.hpp"
#include "pch.hpp" // IWYU pragma: export

#include "Util/Renderer.hpp"
#include "Util/Time.hpp"
#include "Util/Transform.hpp"
#include "Util/Input.hpp"
#include "Util/image.hpp"
#include "config.hpp"

Arrow::Arrow() : m_Giraffe_(nullptr), m_Enemy_(nullptr) {
    // 構造元的具體實現
}

// void Arrow::setTarget(Giraffe* giraffe) {
//     m_Giraffe_ = giraffe;
//     m_PlayerCoordinate = m_Giraffe_ ->coordinate();
// }
void Arrow::setTarget(std::shared_ptr<Giraffe> giraffe) {
    m_Giraffe_ = giraffe;
    m_PlayerCoordinate = m_Giraffe_ ->coordinate();
}

// void Arrow::setTarget(Enemy* enemy) {
//     m_Enemy_ = enemy;
//     m_EnemyCoordinate = m_Enemy_ ->coordinate();
// }
void Arrow::setTarget(std::shared_ptr<Enemy> enemy) {
    m_Enemy_ = enemy;
    m_EnemyCoordinate = m_Enemy_ ->coordinate();
}
void Arrow::setTargets(std::vector<std::shared_ptr<Enemy>>& enemies) {
    m_Enemies.clear();
    for (auto enemy = enemies.begin(); enemy != enemies.end(); ++enemy) {
        m_Enemies.push_back(*enemy);
    }
}

void Arrow::Start(){
    // std::cout << "Shoot Arrow" << std::endl;
    this -> SetDrawable(std::make_shared<Util::Image>("../assets/sprites/arrow.png"));
    this -> SetZIndex(6);

    m_ShouldDelete = false;

    m_Direction = glm::normalize(m_EnemyCoordinate - m_PlayerCoordinate);
    // 初始化箭的位置
    pos = m_PlayerCoordinate;
    
    // 初始化箭的大小
    scale = {0.05f, 0.05f};

    // 初始化箭的旋轉角度
    rotation =atan2(m_Direction.y, m_Direction.x) + 3.1415926f * 1.75f;
    // std::cout << "Arrow rotation: " << rotation << std::endl;

    
}

void Arrow::Update() {
    // 更新箭的位置
    pos += m_Direction * 20.0f; // 假設箭以固定速度移動

    if (pos.y >= static_cast<float>(PTSD_Config::WINDOW_HEIGHT) / 2 ||
        pos.y + static_cast<float>(PTSD_Config::WINDOW_HEIGHT) / 2 <= 0 ||
        pos.x >= static_cast<float>(PTSD_Config::WINDOW_WIDTH) / 2 ||
        pos.x + static_cast<float>(PTSD_Config::WINDOW_WIDTH) / 2 <= 0) {
        m_ShouldDelete = true;
    }
    // 如果箭與敵人重合或正負50個像素，則應該刪除箭
    else {
        for (auto enemy = m_Enemies.begin(); enemy != m_Enemies.end(); ++enemy) {
            if (glm::distance((*enemy)->coordinate(), pos) <= 20.0f) {
                m_ShouldDelete = true;
                (*enemy)->setHP(-(m_Giraffe_ ->getAtk()));
                std::cout << "Arrow hit enemy" << (*enemy)->getHP() <<std::endl;
            // if (enemy != nullptr && glm::distance(m_EnemyCoordinate, pos) <= 50.0f) {
            //     m_ShouldDelete = true;
            //     enemy ->setHP(-(m_Giraffe_ ->getAtk()));
            //     std::cout << "Arrow hit enemy" << enemy->getHP() <<std::endl;
            }
        }
    }
}


glm::vec2 Arrow::coordinate() {
    return pos;
}

bool Arrow::shouldDelete() const {
    return m_ShouldDelete;
}