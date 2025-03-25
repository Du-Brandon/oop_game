#include "Giraffe.hpp"

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

    // m_GiraffeText =
    //     std::make_shared<GiraffeText>("../assets/fonts/Inter.ttf", 50);
    // m_GiraffeText->SetZIndex(this->GetZIndex() - 1);
    // m_GiraffeText->Start();
    // this->AddChild(m_GiraffeText);
}

void Giraffe::Update() {
    // if (enemy_is_empty){
    //     return;
    // }
    glm::vec2 dir_Right = {1, 0}; //長頸鹿的移動方向
    glm::vec2 dir_Left = {-1, 0};
    glm::vec2 dir_Up= {0, 1};
    glm::vec2 dir_Down = {0, -1};
    // Is_move = false;

    // std::cout << pos.x << "   "<< pos.y << std::endl; 

    auto delta = static_cast<float>(Util::Time::GetDeltaTimeMs()) / 2;
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
    if (((Util::Input::IsKeyDown(Util::Keycode::Q) || !anyKeyPressed) && contral_Atk_Speed()) && !enemy_is_empty) {
        ShootArrow();
    }
    for (auto it = m_Arrows.begin(); it != m_Arrows.end();) {
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
        float distance = glm::distance(enemy->coordinate(), pos);
        if (distance < minDistance) {
            minDistance = distance;
            nearestEnemy = enemy;
        }
    }
    return nearestEnemy;
}

void Giraffe::ShootArrow() {
    auto arrow = std::make_shared<Arrow>();
    arrow->setTarget(shared_from_this());
    arrow->setTarget(checkNearestEnemy());
    // std::cout << "Shoot Arrow" << std::endl;
    arrow->Start();
    // this->AddChild(arrow);
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
    if (enemy == nullptr ||enemy->getVisible() == false) {
        return;
    }
    m_Enemies.push_back(enemy);
}

void Giraffe::SetEnemies(std::vector<std::shared_ptr<Enemy>> enemies) {
    m_Enemies.clear();
    for (auto &enemy : enemies) {
        if (enemy->getVisible() == false) {
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

