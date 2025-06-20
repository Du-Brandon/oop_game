#include "EnemyArrow.hpp"
#include <string>

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

void EnemyArrow::Start(std::string image_path , glm::vec2 direction, std::string enemy_arrow_name, bool rebound) {
    if (image_path == "") {
        image_path = "../assets/sprites/redball.png"; // 使用默認圖片路徑
    }
    this->SetDrawable(std::make_shared<Util::Image>(image_path));
    this->SetZIndex(6);

    shoot_speed = 6.0f; // Initialize shoot_speed

    m_ShouldDelete = false;

    if (rebound){
        m_Rebound = rebound;
    }

    m_Direction = glm::normalize(m_PlayerCoordinate - m_EnemyCoordinate);
    m_Direction += direction; // 設置箭的方向

    // 初始化箭的位置
    pos = m_EnemyCoordinate;

    // 初始化箭的大小
    scale = {0.5f, 0.5f};

    this->m_enemy_arrow_name = enemy_arrow_name; // 設置箭的名稱
    // // 初始化箭的旋轉角度
    rotation = atan2(m_Direction.y, m_Direction.x) + 3.1415926f ;
}

void EnemyArrow::Update(){
    pos += m_Direction * shoot_speed; // 假設箭以固定速度移動;
    
    if (m_Wall-> boundary_collision_check_leftright(pos , "arrow") == "right" || m_Wall->boundary_collision_check_leftright(pos, "arrow") == "left") {
        if (m_Rebound) {
            m_Direction.x = -m_Direction.x; // 反彈
            m_LifeCycle++;
            if (m_LifeCycle >= 3) { // 反彈三次後刪除箭
                m_ShouldDelete = true;
            }
        } else {
            m_ShouldDelete = true; // 不反彈則刪除箭
        }
    }
    else if (m_Wall->boundary_collision_check_updown(pos, "arrow") == "up" || m_Wall->boundary_collision_check_updown(pos, "arrow") == "down") {
        if (m_Rebound) {
            m_Direction.y = -m_Direction.y; // 反彈
            m_LifeCycle++;
            if (m_LifeCycle >= 3) { // 反彈三次後刪除箭
                m_ShouldDelete = true;
            }
        } else {
            m_ShouldDelete = true; // 不反彈則刪除箭
        }
    }
    else if (m_Wall -> boundary_collision_check_leftright(pos, "arrow") == "lr" || m_Wall -> boundary_collision_check_updown(pos, "arrow") == "ud") {
        m_ShouldDelete = true;
    }
    else {
        if ((glm::distance(m_PlayerCoordinate,pos)) <=18.0f) {
            m_ShouldDelete = true;
            m_Giraffe_->addHP(- (m_Enemy_->getAtk()));
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
            m_Giraffe_->addHP(- (m_Enemy_->getAtk()));
            std::cout << "Arrow hit player" << m_Giraffe_->getHP() << std::endl;
        }
    }
}

void EnemyArrow::Setspeed(float speed) {
    shoot_speed = speed; // 設置箭的速度
}

glm::vec2 EnemyArrow::coordinate() {
    return pos;
}

bool EnemyArrow::shouldDelete() const {
    return m_ShouldDelete;
}
