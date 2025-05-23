#include "Giraffe.hpp"
#include "log_my.hpp"

#include <cmath>
#include <iostream>
#include <chrono>
#include <string>
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
    arrowCooldown = std::chrono::high_resolution_clock::now(); // 初始化 arrowCooldown

    m_hp_pic -> Start(pos);
    m_hp_pic -> set_maxhp(m_HP);
    this -> AddChild(m_hp_pic);

    m_exp_pic -> Start();
    m_exp_pic -> set_maxexp(m_exp_list);
    this -> AddChild(m_exp_pic);

    std::vector<std::string> skill_list_name = {"double_arrow", "rebound_arrow", "skill_smart", "skill_4"}; // 技能名稱列表

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
        std::string pos_str = std::to_string(pos.x) + " " + std::to_string(pos.y);
        Logger::info("Giraffe position: " + pos_str);
    }

    //按Q鍵測試弓箭
    if (((Util::Input::IsKeyDown(Util::Keycode::Q) || !anyKeyPressed) && (contral_Atk_Speed() )) && !enemy_is_empty && m_Enemies.size() > 0) {
        ShootArrow(bool_skill_double_arrow, false );
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

    if (std::get<0>(double_arrow_is_shoot) && m_Enemies.size() > 0) {
        skill_double_arrow();
    }

    if (m_hp_pic) {
        m_hp_pic->setpic(m_HP);
        m_hp_pic->Update(pos);
    } else {
        Logger::warn("m_hp_pic is nullptr in Giraffe::Update");
    }

    if (bool_skill_invincible){
        skill_invincible_time_count++;
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

void Giraffe::ShootArrow(int double_arrow , bool rebound_arrow) {
    auto arrow = std::make_shared<Arrow>();
    if (!arrow) {
        Logger::error("Failed to create arrow in Giraffe::ShootArrow");
        return;
    }
    arrow->setTarget(shared_from_this());
    arrow->setTarget(checkNearestEnemy());
    arrow->setWall(m_Wall);
    // std::cout << "Shoot Arrow" << std::endl;
    if (double_arrow > 0) {
        arrow->Start();
        std::get<0>(double_arrow_is_shoot) = true; // 準備設第二發箭
        // double_arrow_is_shoot = true; // 準備設第二發箭
        arrowCooldown = std::chrono::high_resolution_clock::now();

    } 
    else{
        arrow->Start();
    }
    
    if (double_arrow) {
        // arrow->setDoubleArrow();
    }

    if (skill_back_arrow_count >= 1){
        Logger::info("Giraffe shoot back arrow");
        auto back_arrow = std::make_shared<Arrow>();
        if (!back_arrow) {
            Logger::error("Failed to create back arrow in Giraffe::ShootArrow");
            return;
        }
        back_arrow->setTarget(shared_from_this());
        back_arrow->setTarget(checkNearestEnemy());
        back_arrow->setWall(m_Wall);
        back_arrow->Start_b("back_arrow");

        m_Arrows.push_back(back_arrow); // 將箭存儲到向量中
        this->AddChild(back_arrow);
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

int Giraffe::getAtk()  {
    if (bool_skill_angry ){
        // 計算當前血量與最大血量的比例
        float hp_ratio = static_cast<float>(m_HP) / max_hp;

        // 使用非線性公式計算倍率（例如：2 - sqrt(hp_ratio)）
        float multiplier = 2.0f - std::sqrt(hp_ratio);

        // 確保倍率不低於 1 倍
        multiplier = std::max(multiplier, 1.0f);
    }
    return atk;
}

void Giraffe::setAtk(int atk) {
    this->atk += atk;
}

void Giraffe::setAtk_speed(float atk_speed) {
    this->atk_speed = this->atk_speed - atk_speed;
}

float Giraffe::getAtk_speed() const {
    return atk_speed;
}

void Giraffe::addHP(int hp) {
    if (hp < 0 && bool_skill_invincible && skill_invincible_time_count > 1000 && skill_invincible_time_count < 1080) { 
        // 如果使用了無敵技能，則不減少血量
        if (skill_invincible_time_count > 1080) {
            skill_invincible_time_count = 0; // 重置計數器
        }
        return;
    }
    m_HP += hp;
    if (m_HP > max_hp) {
        m_HP = max_hp; // 確保血量不會超過最大值
    }
}

void Giraffe::setHP(int hp) {
    m_HP = hp;
}

int Giraffe::getHP() const {
    return m_HP;
}

void Giraffe::addMaxHP(int max_hp) {
    this->max_hp += max_hp;
    m_hp_pic->set_maxhp(this->max_hp);
    m_HP += max_hp; // 增加當前血量
}

void Giraffe::setExp(int exp) {
    if (bool_skill_smart) {
        exp = exp * 2; // 如果使用技能，經驗值翻倍
    }
    this->exp += exp;
    m_exp_pic->add_exp(exp);
}

int Giraffe::getExp() const {
    return exp;
}

int Giraffe::getLevel() const {
    return m_exp_pic->getLevel();
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

void Giraffe::cleararrow() {
    if (m_Arrows.empty()) {
        // Logger::warn("m_Arrows is empty in Giraffe::cleararrow");
        return;
    }
    for (auto it = m_Arrows.begin(); it != m_Arrows.end();) {
        this->RemoveChild(*it); // 刪除箭
        it = m_Arrows.erase(it); // 刪除箭並更新迭代器

    }
    
}


// skill function

void Giraffe::addSkill_double_arrow() {
    std::get<0>(double_arrow_is_shoot) = true; // 設置雙發箭的狀態
    std::get<2>(double_arrow_is_shoot) += 1; // 設置雙發箭的發射次數
}

void Giraffe::skill_double_arrow() {
    // 技能1
    now = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration = now - arrowCooldown;
    // std::cout << "delta" << delta << std::endl;
    // std::cout << duration.count() << std::endl;
    if ((duration.count())*1000 >=6 * delta) {
        ShootArrow(false, false); // 發射第二發箭
        std::get<1>(double_arrow_is_shoot) -= 1; // 減少發射次數
        if (std::get<1>(double_arrow_is_shoot) <= 0) {
            std::get<0>(double_arrow_is_shoot) = false; // 重置技能狀態
            std::get<1>(double_arrow_is_shoot) = std::get<2>(double_arrow_is_shoot); // 重置發射次數
            return;
        }
        arrowCooldown = std::chrono::high_resolution_clock::now(); // 更新冷卻時間
        // double_arrow_is_shoot = false; // 重置技能狀態
    }

}
