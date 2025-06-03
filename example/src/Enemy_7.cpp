#include "log_my.hpp"
#define _USE_MATH_DEFINES // for C++

#include "Enemy_7.hpp"
#include "config.hpp"
#include "Util/Time.hpp"


#include <glm/fwd.hpp>
#include <iostream>
#include <memory>

void Enemy_7::Start(glm::vec2 coordinate) {
    // Logger::info("Enemy_7 Start");
    this->SetDrawable(
    std::make_shared<Util::Image>("../assets/sprites/enemy.png"));
    this->SetZIndex(5);

    m_HP = 400;
    m_atk = 30;
    pos = coordinate;
    scale = {0.2f, 0.2f};
    move_speed = 2.0f;

    enemy_hp_start();

    if (m_attack){
        m_attack -> Set_giraffe_pos(m_Giraffe->coordinate());
        m_attack -> Set_enemy_pos(pos);
        m_attack->Start();
        this->AddChild(m_attack);
    }
    else{
        Logger::warn("m_attack is null");
    }
}

void Enemy_7::Update() {
    if (m_Visible == false){
        for (auto it = m_Arrows.begin(); it != m_Arrows.end();) {
            this->RemoveChild(*it);
            it = m_Arrows.erase(it); // 刪除箭
        }
        m_attack->End();
        return;
    }

    is_burning();

    if (count > atk_speed - 60 and count < atk_speed) {
        m_attack -> Set_giraffe_pos(m_Giraffe->coordinate());
        m_attack->run(pos);
    }
    else if(count >= atk_speed) {
        m_attack->End();
        shoot();
        count = 0;
        shoot_count = 0;
    }
    else{
        if (count >= 70 && count <=170){
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

    count ++;

    enemy_hp_update();
}

glm::vec2 Enemy_7::move() {
    if (count >= 70 && !decide_dir){
        decide_dir = true;
        dir = randomMove('z');
    }
    else if (count >= 170 && decide_dir){
        decide_dir = false;
    }
    return dir;
}

void Enemy_7::shoot(){
    glm::vec2 toGiraffe = m_Giraffe->coordinate() - pos;
    // 計算敵人到長頸鹿的距離


    // 生成一個子彈
    std::shared_ptr<EnemyArrow> m_arrow = std::make_shared<EnemyArrow>();

    m_arrow->setTarget(shared_from_this());
    m_arrow->setTarget(m_Giraffe);
    m_arrow->setWall(m_wall);
    m_arrow->Start("../assets/sprites/enemyarrow.png");
    m_arrow->Setspeed(18.0f); // 設置箭的速度
    m_Arrows.push_back(m_arrow); // 將箭存儲到向量中
    this->AddChild(m_arrow);
}

void Enemy_7_attack::Start(){
    this->SetDrawable(
    std::make_shared<Util::Image>("../assets/other/red.png"));
    this->SetZIndex(4);

    this->SetPivot(glm::vec2 (1,0));

    Logger::info("Enemy_7_attack Start");
    pos = enemy_pos;

    this->SetVisible(false);
}

void Enemy_7_attack::run(glm::vec2 enemy_pos) {
    // 計算敵人到長頸鹿的距離，然後縮放圖片
    this->SetVisible(true);
    pos = enemy_pos;
    glm::vec2 toGiraffe = giraffe_pos - enemy_pos;
    float distance = std::sqrt(toGiraffe.x * toGiraffe.x + toGiraffe.y * toGiraffe.y);
    scale = glm::vec2(distance/2,1); // 根據距離縮放圖片
    rotation = atan2(toGiraffe.y, toGiraffe.x) + M_PI; // 計算旋轉角度
}

void Enemy_7_attack::End(){
    this->SetVisible(false);
    // Logger::info("Enemy_7_attack End");
}

void Enemy_7_attack::Set_giraffe_pos(glm::vec2 giraffe_pos){
    this->giraffe_pos = giraffe_pos;
    // Logger::info("Set giraffe pos");
}

void Enemy_7_attack::Set_enemy_pos(glm::vec2 enemy_pos){
    this->enemy_pos = enemy_pos;
    // Logger::info("Set enemy pos");
}