#include "Giraffe.hpp"
#include "log_my.hpp"

#include <cmath>
#include <iostream>
#include <chrono>
#include <vector>

#include "Util/Image.hpp"
#include "Util/Time.hpp"
#include "Util/Transform.hpp"
#include "Util/Input.hpp"

#include "config.hpp"

void Giraffe::Start() {
    this->SetDrawable(
        std::make_shared<Util::Image>("../assets/sprites/sticker.png"));
    this->SetZIndex(6);
    scale = glm::vec2(0.25f, 0.25f);
    pos = glm::vec2(-100, 0);

    start = std::chrono::high_resolution_clock::now();
    
    m_hp_pic -> Start(pos);
    m_hp_pic -> set_maxhp(m_HP);
    this -> AddChild(m_hp_pic);
    // m_GiraffeText =
    //     std::make_shared<GiraffeText>("../assets/fonts/Inter.ttf", 50);
    // m_GiraffeText->SetZIndex(this->GetZIndex() - 1);
    // m_GiraffeText->Start();
    // this->AddChild(m_GiraffeText);

    std::vector<std::string> skill_list_name = {"double_arrow", "rebound_arrow", "skill_smart", "skill_4"}; // 技能名稱列表
    bool skill_double_arrow = false; // 判斷技能1是否被使用
    bool skill_rebound_arrow = false; // 判斷技能2是否被使用
    bool skill_smart = false; // 判斷技能3是否被使用
    bool skill_4 = false; // 判斷技能4是否被使用
}

void Giraffe::Update() {

    if (!m_Wall) {
        Logger::error("m_Wall is nullptr in Giraffe::Update");
        return;
    }

    glm::vec2 dir_Right = {1, 0}; //長頸鹿的移動方向
    glm::vec2 dir_Left = {-1, 0};
    glm::vec2 dir_Up= {0, 1};
    glm::vec2 dir_Down = {0, -1};
    // Is_move = false;

    // std::cout << pos.x << "   "<< pos.y << std::endl; 

    delta = static_cast<float>(Util::Time::GetDeltaTimeMs()) / 2;
    if (((m_Wall->boundary_collision_check_leftright(pos+dir_Right * 9.0f) == "right") && !enemy_is_empty ) ||(m_Wall->boundary_collision_check_leftright(pos+dir_Right * 9.0f) == "lr")) {
        dir_Right.x *= 0;
    }
    else if (m_Wall->boundary_collision_check_leftright(pos+dir_Right * 9.0f) == "right" && enemy_is_empty && !m_Wall->boundary_collision_check_door(pos+dir_Right * 9.0f)) {
        dir_Right.x *= 0;
    }
    if ((m_Wall->boundary_collision_check_leftright(pos+dir_Left * 9.0f) == "left")||(m_Wall->boundary_collision_check_leftright(pos+dir_Left * 9.0f) == "lr")) {
        dir_Left.x *= 0;
    }

    if  ((m_Wall->boundary_collision_check_updown(pos+dir_Up * 9.0f) == "up") || (m_Wall->boundary_collision_check_updown(pos+dir_Up * 9.0f ) == "ud")) {
        dir_Up.y *= 0;
    }
    if ((m_Wall->boundary_collision_check_updown(pos+dir_Down * 9.0f) == "down" )|| (m_Wall->boundary_collision_check_updown(pos+dir_Down * 9.0f) == "ud")) {
        dir_Down.y *= 0;
    }
    // // sonarcloud called it redundant, but ms_t = float is just a coincidence.


    // std::cout << "delta: " << delta << std::endl;
    Util::Transform deltaTransform_Right{
        dir_Right * delta, 0.002F * delta,
        glm::vec2(1, 1) * (std::sin(rotation / 2) + 1.0F) * 100.0F};
    Util::Transform deltaTransform_Left{
        dir_Left * delta, 0.002F * delta,
        glm::vec2(1, 1) * (std::sin(rotation / 2) + 1.0F) * 100.0F};
    Util::Transform deltaTransform_Up{
        dir_Up * delta, 0.002F * delta,
        glm::vec2(1, 1) * (std::sin(rotation / 2) + 1.0F) * 100.0F};
    Util::Transform deltaTransform_Down{
        dir_Down * delta, 0.002F * delta,
        glm::vec2(1, 1) * (std::sin(rotation / 2) + 1.0F) * 100.0F};
    // pos += deltaTransform.translation;
    // rotation += deltaTransform.rotation;
    bool anyKeyPressed = false;

    if (Util::Input::IsKeyPressed(Util::Keycode::D)) {
        pos += deltaTransform_Right.translation;
        anyKeyPressed = true;
    }

    if (Util::Input::IsKeyPressed(Util::Keycode::A)) {
        pos += deltaTransform_Left.translation;
        anyKeyPressed = true;
    }

    if (Util::Input::IsKeyPressed(Util::Keycode::W)) {
        pos += deltaTransform_Up.translation;
        anyKeyPressed = true;
    }

    if (Util::Input::IsKeyPressed(Util::Keycode::S)) {
        pos += deltaTransform_Down.translation;
        anyKeyPressed = true;
    }

    // 按下P取得位置
    if(Util::Input::IsKeyDown(Util::Keycode::P)){
        std::cout << pos.x << "   "<< pos.y << std::endl; 
    }

    //按Q鍵測試弓箭
    if (((Util::Input::IsKeyDown(Util::Keycode::Q) || !anyKeyPressed) && (contral_Atk_Speed() )) && !enemy_is_empty && m_Enemies.size() > 0) {
        ShootArrow(false, false);
    }
    for (auto it = m_Arrows.begin(); it != m_Arrows.end();) {
        if (!(*it)) {
            Logger::warn("Arrow is nullptr in Giraffe::Update");
            it = m_Arrows.erase(it); // 刪除箭並更新迭代器
            continue;
        }
        (*it)->setTargets(m_Enemies);
        (*it)->Update();
        if ((*it)->shouldDelete()) {
            this->RemoveChild(*it); // 刪除箭
            it = m_Arrows.erase(it); // 刪除箭並更新迭代器
            // std::cout << "Arrow deleted" << std::endl;
        } else {
            ++it;
        }
    }

    if (m_hp_pic) {
        m_hp_pic->setpic(m_HP);
        m_hp_pic->Update(pos);
    } else {
        Logger::warn("m_hp_pic is nullptr in Giraffe::Update");
    }

    // m_GiraffeText->Update();
}

void Giraffe::set_enemy_is_empty(bool is_empty) {
    enemy_is_empty = is_empty;
}

bool Giraffe::contral_Atk_Speed() {
    now = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration = now - start;
    if (duration.count() >= atk_speed) {
        start = std::chrono::high_resolution_clock::now();
        return true;
    }
    return false;
}

std::shared_ptr<Enemy> Giraffe::checkNearestEnemy() {
    std::shared_ptr<Enemy> nearestEnemy = nullptr;
    float minDistance = 1000000.0f;
    for (auto &enemy : m_Enemies) {
        if (!enemy) {
            Logger::warn("Enemy is nullptr in Giraffe::checkNearestEnemy");
            continue;
        }
        float distance = glm::distance(enemy->coordinate(), pos);
        if (distance < minDistance) {
            minDistance = distance;
            nearestEnemy = enemy;
        }
    }
    return nearestEnemy;
}

void Giraffe::ShootArrow(bool double_arrow , bool rebound_arrow) {
    auto arrow = std::make_shared<Arrow>();
    if (!arrow) {
        Logger::error("Failed to create arrow in Giraffe::ShootArrow");
        return;
    }
    arrow->setTarget(shared_from_this());
    arrow->setTarget(checkNearestEnemy());
    arrow->setWall(m_Wall);
    // std::cout << "Shoot Arrow" << std::endl;
    if (rebound_arrow) {
        arrow->Start();
        double_arrow_is_shoot = true; // 準備設第二發箭
        auto arrowCooldown = std::chrono::high_resolution_clock::now();

    } 
    else{
        arrow->Start();
    }
    
    if (double_arrow) {
        // arrow->setDoubleArrow();
    }
    
    m_Arrows.push_back(arrow); // 將箭存儲到向量中
    this->AddChild(arrow);
}

glm::vec2 Giraffe::coordinate() {
    return pos;
}

void Giraffe::setpos(glm::vec2 position) {
    pos = position;
}

int Giraffe::getAtk() const {
    return atk;
}

void Giraffe::setAtk(int atk) {
    this->atk += atk;
}

int Giraffe::getHP() const {
    return m_HP;
}

void Giraffe::setHP(int hp) {
    m_HP += hp;
}

void Giraffe::setExp(int exp) {
    this->exp += exp;
}

int Giraffe::getExp() const {
    return exp;
}

void Giraffe::SetEnemy(std::shared_ptr<Enemy> enemy) {
    m_Enemy = enemy;
}

void Giraffe::SetEnemies(std::shared_ptr<Enemy> enemy) {
    if (enemy == nullptr ||enemy->getVisible() == false || enemy->getName() == "Angel") {
        return;
    }
    m_Enemies.push_back(enemy);
}

void Giraffe::SetEnemies(std::vector<std::shared_ptr<Enemy>> enemies) {
    m_Enemies.clear();
    for (auto &enemy : enemies) { //|| enemy->getName() == "Angel"
        if (enemy->getVisible() == false || enemy->getName() == "Angel") {
            continue;
        }
        m_Enemies.push_back(enemy);
    }
}

void Giraffe::Setwall(std::shared_ptr<Wall> wall) {
    m_Wall = wall;
}

void Giraffe::ClearEnemies() {
    m_Enemies.clear();
}

// skill function
void Giraffe::judge_skill() {
    // 判斷技能
    
}

void Giraffe::skill_double_arrow() {
    // 技能1
    now = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration = now - arrowCooldown;
    if (duration.count() >= 2 * delta) {
        ShootArrow(false, false); // 發射第二發箭
        double_arrow_is_shoot = false; // 重置技能狀態
    }

}
