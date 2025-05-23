#include "Enemy_4.hpp"
#include "log_my.hpp"
#include <cstdlib>

// 新式寫法
void Enemy_4::Start(glm::vec2 coordinate) {
    pos = coordinate;
    scale = {0.2f, 0.2f};
    move_speed = 1.0f;
    m_HP = 250;
    this->SetZIndex(5);
    this->SetDrawable(std::make_shared<Util::Image>("../assets/sprites/enemy.png"));

    enemy_hp_start();
}

void Enemy_4::Update() {
    if (m_Visible == false){
        for (auto it = m_stones.begin(); it != m_stones.end();) {
            this->RemoveChild(*it);
            it = m_stones.erase(it); // 刪除箭
        }
        return;
    }
    
    if(count >= atk_speed) {
        shoot();
        count = 0;
        rotation_count = 0;
    }
    else{
        if (count >= 90 && count <=260){
            dir = move();
            
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
        }
        count ++;

    }
    if (rotation_count <= 19 || rotation_count >= 341) {
        rotation += glm::radians(18.0f); // 每次更新旋轉 36 度（轉換為弧度）
        rotation_count ++ ;
    }
    else if(rotation_count ==360){
        rotation_count = 0;
    }

    for (auto it = m_stones.begin(); it != m_stones.end();) {
        (*it)->setTarget(m_Giraffe);
        (*it)->Update();
        if ((*it)->shouldDelete()) {
            this->RemoveChild(*it);
            it = m_stones.erase(it); // 刪除箭
        } else {
            ++it;
        }
    }
    
    enemy_hp_update();
}


// 隨便移動
glm::vec2 Enemy_4::move() {
    if (count >= 15 && !decide_dir){
        decide_dir = true;
        dir = randomMove('z');
    }
    else if (count <= 45 && decide_dir){
        decide_dir = false;
    }
    return dir;
}

// 同時向giraffe和兩側射擊
void Enemy_4::shoot() {
    glm::vec2 toGiraffe = glm::normalize(m_Giraffe->coordinate() - pos); // 朝向玩家的方向向量

    // 計算左偏 45 度和右偏 45 度的方向向量
    glm::vec2 left45 = glm::vec2(
        toGiraffe.x * cos(glm::radians(45.0f)) - toGiraffe.y * sin(glm::radians(45.0f)),
        toGiraffe.x * sin(glm::radians(45.0f)) + toGiraffe.y * cos(glm::radians(45.0f))
    );

    glm::vec2 right45 = glm::vec2(
        toGiraffe.x * cos(glm::radians(-45.0f)) - toGiraffe.y * sin(glm::radians(-45.0f)),
        toGiraffe.x * sin(glm::radians(-45.0f)) + toGiraffe.y * cos(glm::radians(-45.0f))
    );

    // 創建三顆石頭
    std::shared_ptr<EnemyArrow> m_stone_mid = std::make_shared<EnemyArrow>();
    std::shared_ptr<EnemyArrow> m_stone_left = std::make_shared<EnemyArrow>();
    std::shared_ptr<EnemyArrow> m_stone_right = std::make_shared<EnemyArrow>();

    // 射向玩家
    stone_shoot(m_stone_mid, toGiraffe);

    // 射向左偏 45 度
    stone_shoot(m_stone_left, left45);

    // 射向右偏 45 度
    stone_shoot(m_stone_right, right45);

    if (bool_logger) {
        Logger::info("Enemy_4 shoot: finish shoot stone to Giraffe and left and right");
    }
}

void Enemy_4::stone_shoot(std::shared_ptr<EnemyArrow> m_stone , glm::vec2 direction) {
    m_stone->setTarget(shared_from_this());
    m_stone->setTarget(m_Giraffe);
    m_stone->setWall(m_wall);
    m_stone->Start("../assets/sprites/redball.png", direction, "stone");
    m_stones.push_back(m_stone); // 將箭存儲到向量中
    this->AddChild(m_stone);
}


