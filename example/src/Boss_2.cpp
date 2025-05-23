#include "Boss.hpp"

#include <random>

void Boss_2::Start(glm::vec2 coordinate) {
    this->SetDrawable(
        std::make_shared<Util::Image>("../assets/sprites/enemy.png"));
    this->SetZIndex(5);
        
    final_wish = "Add player's 200 hp";
    name = "Boss_2";

    m_HP = 2000;
    m_atk = 15;
    exp_supply = 160;
    
    pos = coordinate;
    scale = {0.2f, 0.2f};

    move_speed = 12.0f;
    enemy_hp_start();
}

void Boss_2::Update() {
    if (m_Visible == false){
        for (auto it = m_Arrows.begin(); it != m_Arrows.end();) {
            this->RemoveChild(*it);
            it = m_Arrows.erase(it); // 刪除箭
        }
        return;
    }
    // 輸出新的位置
    // std::cout << "Enemy position: (" << pos.x << ", " << pos.y << ")" << std::endl;

    //  100~300 亂射 400~500 鎖敵連射 600招喚一隻enemy_3
    if (count >= 100 and count < 300 and count % 5 == 0) {
        shoot_random();
    } 
    else if (count >= 400 and count < 500 and count % 5 == 0) {
        shoot();
    }
    else if (count == 350) {
        summon_enemy_3 = true;
    }
    else if (count == count_max) {
        summon_enemy_3 = true;
        count = 0;
    }

    for (auto it = m_Arrows.begin(); it != m_Arrows.end();) {
        (*it)->setTarget(m_Giraffe);
        (*it)->Update(true);
        if ((*it)->shouldDelete()) {
            this->RemoveChild(*it);
            it = m_Arrows.erase(it); // 刪除箭
            // std::cout << "Arrow deleted" << std::endl;
        } else {
            ++it;
        }
    
    }

    enemy_hp_update();

    count ++;
}

void Boss_2::shoot() {
    std::shared_ptr<EnemyArrow> m_Arrow = std::make_shared<EnemyArrow>();
    m_Arrow->setTarget(shared_from_this());
    m_Arrow->setTarget(m_Giraffe);
    m_Arrow->setWall(m_wall);
    m_Arrow->Start();
    m_Arrow->Setspeed(10.0f); // 設置箭的速度
    m_Arrows.push_back(m_Arrow);
    this->AddChild(m_Arrow);
}

glm::vec2 Boss_2::move() {
    return dir;
}

void Boss_2::shoot_random() {
    if (!m_Giraffe) {
        Logger::warn("Giraffe is nullptr, cannot shoot.");
        return;
    }

    // 計算朝向玩家的方向向量
    glm::vec2 toGiraffe = glm::normalize(m_Giraffe->coordinate() - pos);

    // 隨機生成 -45 到 45 度的偏移角度
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> angle_dist(-45.0f, 45.0f);

    float random_angle = angle_dist(gen); // 隨機角度
    float radians = glm::radians(random_angle); // 將角度轉換為弧度

    // 計算偏移後的方向向量
    glm::vec2 adjustedDirection = glm::vec2(
        toGiraffe.x * cos(radians) - toGiraffe.y * sin(radians),
        toGiraffe.x * sin(radians) + toGiraffe.y * cos(radians)
    );

    // 創建箭並射向偏移後的方向
    std::shared_ptr<EnemyArrow> m_Arrow = std::make_shared<EnemyArrow>();
    m_Arrow->setTarget(shared_from_this());
    m_Arrow->setTarget(m_Giraffe);
    m_Arrow->setWall(m_wall);
    m_Arrow->Start("", adjustedDirection); // 假設 Start 支援方向參數
    m_Arrow->Setspeed(7.5f); // 設置箭的速度
    m_Arrows.push_back(m_Arrow);
    this->AddChild(m_Arrow);

    Logger::info("Boss_2 shoot_random: shot arrow with random angle offset towards Giraffe.");
}

