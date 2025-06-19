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

// Giraffe = 玩家，不要問為什麼

void Giraffe::Start() {

    this->SetDrawable(
        std::make_shared<Util::Image>("../assets/sprites/sticker.png"));
    this->SetZIndex(6);
    scale = glm::vec2(0.25f, 0.25f);
    pos = glm::vec2(-420, 0);

    start = std::chrono::high_resolution_clock::now();
    arrowCooldown = std::chrono::high_resolution_clock::now(); // 初始化 arrowCooldown

    m_hp_pic -> Start(pos);
    m_hp_pic -> set_maxhp(m_HP);
    this -> AddChild(m_hp_pic);

    m_exp_pic -> Start();
    m_exp_pic -> set_maxexp(m_exp_list);
    this -> AddChild(m_exp_pic);

    m_Giraffe_atk_Text->Start("atk", glm::vec2(-400, -300), shared_from_this());
    m_Giraffe_hp_Text->Start("hp", glm::vec2(-200, -300), shared_from_this());
    // m_Giraffe_if_invincible_Text->Start("是否無敵", glm::vec2(00, -300), shared_from_this());
    m_GiraffeTexts.push_back(m_Giraffe_atk_Text);
    m_GiraffeTexts.push_back(m_Giraffe_hp_Text);
    // m_GiraffeTexts.push_back(m_Giraffe_if_invincible_Text);

    this->AddChild(m_Giraffe_atk_Text);
    this->AddChild(m_Giraffe_hp_Text);
    // this->AddChild(m_Giraffe_if_invincible_Text);
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

    if (m_Wall->boundary_collision_check_updown(pos) == "ud" and m_Wall->boundary_collision_check_leftright(pos) == "lr") {
        dir_Right.x = 1;
        dir_Left.x = 1;
        dir_Up.y = 1;
        dir_Down.y = 1;
    }

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
        std::string pos_str = std::to_string(pos.x) + ", " + std::to_string(pos.y);
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

    // debug
    if (Util::Input::IsKeyDown(Util::Keycode::NUM_1)) {
        this->setAtk(100);
        Logger::info("用外掛讓攻擊變成" + std::to_string(this->getAtk()));
    }
    if (Util::Input::IsKeyDown(Util::Keycode::NUM_2)) {
        this->addMaxHP(150);
        Logger::info("用外掛讓血量變成" + std::to_string(this->getHP()));
    }
    if (Util::Input::IsKeyDown(Util::Keycode::NUM_3)) {
        this->setAtk_speed(atk_speed* 0.1f);
        Logger::info("用外掛讓攻擊速度變成" + std::to_string(this->getAtk_speed()));
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

    for (const auto& text : m_GiraffeTexts) {
        text->Update();
    }
}

void Giraffe::End() {

    m_Arrows.clear();
    m_Enemies.clear();

    m_hp_pic->SetVisible(false);
    m_exp_pic->End();
    for (const auto& text : m_GiraffeTexts) {
        text->SetVisible(false);
    }
    this->SetVisible(false); // 隱藏長頸鹿對象
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

    if (right_left_side_arrow >=1){
        auto right_arrow = std::make_shared<Arrow>();
        if (!right_arrow) {
            Logger::error("Failed to create right arrow in Giraffe::ShootArrow");
            return;
        }
        right_arrow->setTarget(shared_from_this());
        right_arrow->setTarget(checkNearestEnemy());
        right_arrow->setWall(m_Wall);
        right_arrow->Start_b("right_arrow");
        m_Arrows.push_back(right_arrow); // 將箭存儲到向量中
        this->AddChild(right_arrow);

        auto left_arrow = std::make_shared<Arrow>();
        if (!left_arrow) {
            Logger::error("Failed to create left arrow in Giraffe::ShootArrow");
            return;
        }
        left_arrow->setTarget(shared_from_this());
        left_arrow->setTarget(checkNearestEnemy());
        left_arrow->setWall(m_Wall);
        left_arrow->Start_b("left_arrow");
        m_Arrows.push_back(left_arrow); // 將箭存儲到向量中
        this->AddChild(left_arrow);
    }
    if (incline_arrow >= 1) {
        auto incline_arrow_1 = std::make_shared<Arrow>();
        if (!incline_arrow_1) {
            Logger::error("Failed to create incline arrow in Giraffe::ShootArrow");
            return;
        }
        incline_arrow_1->setTarget(shared_from_this());
        incline_arrow_1->setTarget(checkNearestEnemy());
        incline_arrow_1->setWall(m_Wall);
        incline_arrow_1->Start_b("incline_arrow_1");
        m_Arrows.push_back(incline_arrow_1); // 將箭存儲到向量中
        this->AddChild(incline_arrow_1);

        auto incline_arrow_2 = std::make_shared<Arrow>();
        if (!incline_arrow_2) {
            Logger::error("Failed to create incline arrow in Giraffe::ShootArrow");
            return;
        }
        incline_arrow_2->setTarget(shared_from_this());
        incline_arrow_2->setTarget(checkNearestEnemy());
        incline_arrow_2->setWall(m_Wall);
        incline_arrow_2->Start_b("incline_arrow_2");
        m_Arrows.push_back(incline_arrow_2); // 將箭存儲到向量中
        this->AddChild(incline_arrow_2);
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

        return static_cast<int>(atk * multiplier); // 返回計算後的攻擊力
    }
    return atk;
}

void Giraffe::setAtk(int atk) {
    this->atk += atk;
}

void Giraffe::setAtk_speed(float atk_speed) {
    if (atk_speed < 0.3) {
        Logger::warn("Attack speed cannot be less than 0.3 in Giraffe::setAtk_speed");
        return;
    }
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

void GiraffeText::Start(std::string word, glm::vec2 pos, std::shared_ptr<Giraffe> giraffe) {
    m_Word = word;
    this->giraffe = giraffe;
    m_Text = std::make_unique<Util::Text>(m_Font, m_Size, fmt::format(word , "{}", 0),
        Util::Color::FromRGB(255, 255, 255));

    this->pos = pos; // 設置位置

    SetDrawable(m_Text);
    
}

void GiraffeText::Update() {
    if (m_Word == "atk"){
        parameter = std::to_string(giraffe->getAtk());
    }
    else if (m_Word == "hp") {
        parameter = std::to_string(giraffe->getHP());
    }
    else if (m_Word == "是否無敵") {
        if (giraffe->bool_skill_invincible) {
            parameter = "是"; 
        }
        else {
            parameter = "否"; 
        }
    }
    else {
        parameter = "0"; // 預設值
    }
    m_Text->SetText(fmt::format( "{}", m_Word + ":" + parameter));
};

void GiraffeText::end() {
    m_Text->SetText(fmt::format("{}"));
}