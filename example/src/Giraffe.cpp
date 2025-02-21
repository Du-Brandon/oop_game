#include "Giraffe.hpp"

#include <cmath>
#include <iostream>
#include <chrono>

#include "Util/Image.hpp"
#include "Util/Time.hpp"
#include "Util/Transform.hpp"
#include "Util/Input.hpp"

#include "config.hpp"

void Giraffe::Start() {
    this->SetDrawable(
        std::make_shared<Util::Image>("../assets/sprites/sticker.png"));
    this->SetZIndex(6);
    scale = glm::vec2(0.4f, 0.4f);
    
    start = std::chrono::high_resolution_clock::now();

    m_GiraffeText =
        std::make_shared<GiraffeText>("../assets/fonts/Inter.ttf", 50);
    m_GiraffeText->SetZIndex(this->GetZIndex() - 1);
    m_GiraffeText->Start();
    this->AddChild(m_GiraffeText);
}

void Giraffe::Update() {
    glm::vec2 dir_Right = {1, 0}; //長頸鹿的移動方向
    glm::vec2 dir_Left = {-1, 0};
    glm::vec2 dir_Up= {0, 1};
    glm::vec2 dir_Down = {0, -1};
    // Is_move = false;
    
    // 此段已寫至hpp
    // auto &pos = m_Transform.translation; // 長頸鹿的位置
    // auto &scale = m_Transform.scale; // 長頸鹿的大小
    // auto &rotation = m_Transform.rotation; //  長頸鹿的旋轉角度
    // glm::vec2 &pos = m_Transform.translation; // 長頸鹿的位置
    // glm::vec2 &scale = m_Transform.scale; // 長頸鹿的大小
    // float &rotation = m_Transform.rotation; // 長頸鹿的旋轉角度

    // std::cout << pos.y << std::endl;
    if (pos.y >= static_cast<float>(PTSD_Config::WINDOW_HEIGHT) / 2) {
        dir_Up.y *= 0;
    }
    else if (pos.y + static_cast<float>(PTSD_Config::WINDOW_HEIGHT) / 2 <= 0) {
        dir_Down.y *= 0;
    }

    if (pos.x >= static_cast<float>(PTSD_Config::WINDOW_WIDTH) / 2) {
        dir_Right.x *= 0;
    }
    else if (pos.x + static_cast<float>(PTSD_Config::WINDOW_WIDTH) / 2 <= 0) {
        dir_Left.x *= 0;
    }

    // // sonarcloud called it redundant, but ms_t = float is just a coincidence.
    auto delta = static_cast<float>(Util::Time::GetDeltaTimeMs()) / 2;

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


    //按Q鍵測試弓箭
    if ((Util::Input::IsKeyDown(Util::Keycode::Q) || !anyKeyPressed) && contral_Atk_Speed()) {
        ShootArrow();
    }
    for (auto it = m_Arrows.begin(); it != m_Arrows.end();) {
        (*it)->setTarget(m_Enemy.get());
        (*it)->Update();
        if ((*it)->shouldDelete()) {
            this->RemoveChild(*it); // 刪除箭
            it = m_Arrows.erase(it); // 刪除箭並更新迭代器
            std::cout << "Arrow deleted" << std::endl;
        } else {
            ++it;
        }
    }

    m_GiraffeText->Update();
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

void Giraffe::ShootArrow() {
    auto arrow = std::make_shared<Arrow>();
    arrow->setTarget(this);
    arrow->setTarget(m_Enemy.get());
    // std::cout << "Shoot Arrow" << std::endl;
    arrow->Start();
    // this->AddChild(arrow);
    m_Arrows.push_back(arrow); // 將箭存儲到向量中
    this->AddChild(arrow);
}

glm::vec2 Giraffe::coordinate() {
    return pos;
}

int Giraffe::getAtk() const {
    return atk;
}

int Giraffe::getHP() const {
    return m_HP;
}

void Giraffe::setHP(int hp) {
    m_HP += hp;
}

// void Giraffe::setEnemy(std::shared_ptr<Enemy> enemy) {
//     m_Enemies.push_back(enemy);
// }

void Giraffe::setEnemy(std::shared_ptr<Enemy> enemy) {
    m_Enemy = enemy;
}