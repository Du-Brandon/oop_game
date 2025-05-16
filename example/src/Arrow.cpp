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

void Arrow::setTarget(std::shared_ptr<Giraffe> giraffe) {
    m_Giraffe_ = giraffe;
    m_PlayerCoordinate = m_Giraffe_ ->coordinate();
}

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

void Arrow::setWall(std::shared_ptr<Wall> wall) {
    m_Wall = wall;
}

void Arrow::Start(){
    // std::cout << "Shoot Arrow" << std::endl;
    bool_skill_rebound_arrow = m_Giraffe_ ->getSkill_rebound_arrow();
    this -> SetDrawable(std::make_shared<Util::Image>("../assets/sprites/arrow.png"));
    this -> SetZIndex(6);

    m_ShouldDelete = false;

    m_Direction = glm::normalize(m_EnemyCoordinate - m_PlayerCoordinate);
    // 初始化箭的位置
    pos = m_PlayerCoordinate;
    
    // 初始化箭的大小
    scale = {0.03f, 0.03f};

    // 初始化箭的旋轉角度
    rotation =atan2(m_Direction.y, m_Direction.x) + 3.1415926f * 1.75f;
    // std::cout << "Arrow rotation: " << rotation << std::endl;
}

void Arrow::Start(bool rebound_arrow){
    bool rebound = rebound_arrow;
    this->Start();
}

void Arrow::Start_b(std::string skill_name){
    
    if (skill_name == "back_arrow") {
        this -> SetDrawable(std::make_shared<Util::Image>("../assets/sprites/arrow.png"));
        this -> SetZIndex(6);

        m_ShouldDelete = false;
        
        // 方向轉180度
        m_Direction =  glm::normalize(m_PlayerCoordinate - m_EnemyCoordinate);

        // 初始化箭的位置
        pos = m_PlayerCoordinate;
        
        // 初始化箭的大小
        scale = {0.03f, 0.03f};

        // 初始化箭的旋轉角度
        rotation =atan2(m_Direction.y, m_Direction.x) + 3.1415926f * 1.75f;
    }
}

void Arrow::Update() {
    // 更新箭的位置
    Frame_rate += 1; 
    pos += m_Direction * 20.0f; // 假設箭以固定速度移動
    bool_skill_rebound_arrow = m_Giraffe_ ->getSkill_rebound_arrow();

    if (!bool_skill_rebound_arrow){
        if (m_Wall->boundary_collision_check_leftright(pos,"arrow") == "right" || m_Wall->boundary_collision_check_leftright(pos,"arrow") == "left") {
            m_ShouldDelete = true;
            std::cout << "Arrow hit wall" << std::endl;
        }
        else if (m_Wall->boundary_collision_check_updown(pos,"arrow") == "up" || m_Wall->boundary_collision_check_updown(pos,"arrow") == "down") {
            m_ShouldDelete = true;
            std::cout << "Arrow hit wall" << std::endl;
        }
        else if (m_Wall -> boundary_collision_check_leftright(pos,"arrow") == "lr" || m_Wall -> boundary_collision_check_updown(pos,"arrow") == "ud") {
            m_ShouldDelete = true;
            std::cout << "Arrow hit wall" << std::endl;
        }
        
    // 如果箭與敵人重合或正負50個像素，則應該刪除箭
        else {
            for (auto enemy = m_Enemies.begin(); enemy != m_Enemies.end(); ++enemy) {
                if (glm::distance((*enemy)->coordinate(), pos) <= 20.0f) {
                    m_ShouldDelete = true;
                    (*enemy)->setHP(-(m_Giraffe_ ->getAtk()));
                    std::cout << "Arrow hit enemy" << (*enemy)->getHP() <<std::endl;
                }
            }
        }
    }
    else {
        if (Frame_rate >= 150) { // 每180幀檢查一次
            Frame_rate = 0; // 重置幀率計數器
            m_ShouldDelete = true;
        }
        // 反彈箭的邊界檢查
        else if (m_Wall->boundary_collision_check_leftright(pos,"arrow") == "right" || m_Wall->boundary_collision_check_leftright(pos,"arrow") == "left") {
            m_Direction.x *= -1; // 反彈
            rotation = atan2(m_Direction.y, m_Direction.x) + 3.1415926f * 1.75f; // 更新旋轉角度
            std::cout << "Arrow rebound wall" << std::endl;
        }
        else if (m_Wall->boundary_collision_check_updown(pos,"arrow") == "up" || m_Wall->boundary_collision_check_updown(pos,"arrow") == "down") {
            m_Direction.y *= -1; // 反彈
            rotation = atan2(m_Direction.y, m_Direction.x) + 3.1415926f * 1.75f; // 更新旋轉角度
            std::cout << "Arrow rebound wall" << std::endl;
        }
        else if (m_Wall -> boundary_collision_check_leftright(pos,"arrow") == "lr" || m_Wall -> boundary_collision_check_updown(pos,"arrow") == "ud") {
            m_Direction.x *= -1; // 反彈
            m_Direction.y *= -1; // 反彈
            rotation = atan2(m_Direction.y, m_Direction.x) + 3.1415926f * 1.75f; // 更新旋轉角度
            std::cout << "Arrow rebound wall" << std::endl;
        }

        else {
            for (auto enemy = m_Enemies.begin(); enemy != m_Enemies.end(); ++enemy) {
                if (glm::distance((*enemy)->coordinate(), pos) <= 20.0f) {
                    m_ShouldDelete = true;
                    (*enemy)->setHP(-(m_Giraffe_ ->getAtk()));
                    std::cout << "Arrow hit enemy" << (*enemy)->getHP() <<std::endl;
                }
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