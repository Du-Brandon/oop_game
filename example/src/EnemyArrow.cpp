#include "EnemyArrow.hpp"

void EnemyArrow::setTarget(std::shared_ptr<Enemy> enemy) {
    m_Enemy_ = enemy;
    m_EnemyCoordinate = m_Enemy_->coordinate();
}

void EnemyArrow::setTarget(std::shared_ptr<Giraffe> giraffe) {
    m_Giraffe_ = giraffe;
    m_PlayerCoordinate = m_Giraffe_->coordinate();
}

void EnemyArrow::setWall(std::shared_ptr<Wall> wall) {
    m_Wall = wall;
}

void EnemyArrow::Start() {
    this->SetDrawable(std::make_shared<Util::Image>("../assets/sprites/redball.png"));
    this->SetZIndex(6);

    shoot_speed = 6.0f; // Initialize shoot_speed

    m_ShouldDelete = false;

    m_Direction = glm::normalize(m_PlayerCoordinate - m_EnemyCoordinate);

    // 初始化箭的位置
    pos = m_EnemyCoordinate;

    // 初始化箭的大小
    scale = {0.5f, 0.5f};

    // // 初始化箭的旋轉角度
    // rotation = atan2(m_Direction.y, m_Direction.x) + 3.1415926f * 1.75f;
}

void EnemyArrow::Update(){
    pos += m_Direction * shoot_speed; // 假設箭以固定速度移動;
    if (m_Wall-> boundary_collision_check_leftright(pos) == "right" || m_Wall->boundary_collision_check_leftright(pos) == "left") {
        m_ShouldDelete = true;
    }
    else if (m_Wall->boundary_collision_check_updown(pos) == "up" || m_Wall->boundary_collision_check_updown(pos) == "down") {
        m_ShouldDelete = true;
    }
    else if (m_Wall -> boundary_collision_check_leftright(pos) == "lr" || m_Wall -> boundary_collision_check_updown(pos) == "ud") {
        m_ShouldDelete = true;
    }
    else {
        if ((glm::distance(m_PlayerCoordinate,pos)) <=18.0f) {
            m_ShouldDelete = true;
            m_Giraffe_->setHP(- (m_Enemy_->getAtk()));
            std::cout << "Arrow hit player" << m_Giraffe_->getHP() << std::endl;
        }
    }
}

void EnemyArrow::Update(bool ignorewall) {
    pos += m_Direction * shoot_speed; // 假設箭以固定速度移動;
    if (m_Wall-> boundary_collision_check_leftright(pos) == "right" || m_Wall->boundary_collision_check_leftright(pos) == "left") {
        m_ShouldDelete = true;
    }
    else if (m_Wall->boundary_collision_check_updown(pos) == "up" || m_Wall->boundary_collision_check_updown(pos) == "down") {
        m_ShouldDelete = true;
    }
    else {
        if ((glm::distance(m_PlayerCoordinate,pos)) <=18.0f) {
            m_ShouldDelete = true;
            m_Giraffe_->setHP(- (m_Enemy_->getAtk()));
            std::cout << "Arrow hit player" << m_Giraffe_->getHP() << std::endl;
        }
    }
}

glm::vec2 EnemyArrow::coordinate() {
    return pos;
}

bool EnemyArrow::shouldDelete() const {
    return m_ShouldDelete;
}
