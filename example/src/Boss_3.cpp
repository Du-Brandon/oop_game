#include "Boss.hpp"
#include <cmath>

void Boss_3::Start(glm::vec2 coordinate) {
    this->SetDrawable(
        std::make_shared<Util::Image>("../assets/sprites/enemy.png"));
    this->SetZIndex(5);
    
    final_wish = "Add player's 200 hp";
    name = "Boss_3";

    dir = randomMove('z'); // 長頸鹿的移動方向

    m_HP = 2200;
    m_atk = 15;
    exp_supply = 180;

    pos = coordinate;
    scale = {0.2f, 0.2f};

    move_speed = 3.0f;
    enemy_hp_start();
}

void Boss_3::Update() {
    if (m_Visible == false){
        for (auto it = m_Arrows.begin(); it != m_Arrows.end();) {
            this->RemoveChild(*it);
            it = m_Arrows.erase(it); // 刪除箭
        }
        return;
    }

    is_burning();

    // 輸出新的位置
    // std::cout << "Enemy position: (" << pos.x << ", " << pos.y << ")" << std::endl;

    // 確保敵人不會超出視窗範圍
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

    // 100~130 偵，每六偵往玩家射擊，且箭會反彈
    if (count >= 100 && count < 130 && count % 6 == 0) {
        shoot();
    }
    // 150~200 偵，朝玩家移動
    else if (count >= 150 && count < 200) {
        glm::vec2 direction = glm::normalize(m_Giraffe->coordinate() - pos);
        pos += direction * move_speed;
    }
    // 220 偵，米字散射
    else if (count == 220) {
        shoot_diagonal();
    }

    // 270~300 偵，朝玩家移動
    else if (count >= 270 && count < 300) {
        glm::vec2 direction = glm::normalize(m_Giraffe->coordinate() - pos);
        pos += direction * (move_speed + 2.0f);
    }

    // 330 偵，瞬移到玩家位置旁200以外的位置且不能超出強外
    else if (count == 330) {
        glm::vec2 direction = glm::normalize(m_Giraffe->coordinate() - pos);
        pos = m_Giraffe->coordinate() + direction * 100.0f;
        // 確保不超出邊界
        pos.x = std::clamp(pos.x, m_wall->getLeftBoundary(), m_wall->getRightBoundary());
        pos.y = std::clamp(pos.y, m_wall->getTopBoundary(), m_wall->getBottomBoundary());
    }

    if (count >= count_max){
        count = 0; // 重置計數器
    } else {
        count++; // 增加計數器
    }

    if (m_HP <= m_MaxHP / 2){
        move_speed *= 2 ;
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

    enemy_hp_update();
}

void Boss_3::shoot() {

    std::shared_ptr<EnemyArrow> m_Arrow = std::make_shared<EnemyArrow>();
    m_Arrow->setTarget(shared_from_this());
    m_Arrow->setTarget(m_Giraffe);
    m_Arrow->setWall(m_wall);
    m_Arrow->Start("", glm::normalize(m_Giraffe->coordinate() - pos), "arrow", true); // 使用默認圖片路徑和方向，並設置為反彈
    m_Arrow->Setspeed(4.0f); // 設置箭的速度
    m_Arrows.push_back(m_Arrow);
    this->AddChild(m_Arrow);
}

glm::vec2 Boss_3::move() {
    return dir;
}

void Boss_3::shoot_diagonal() {
    // 米字散射(八個方位，速度一樣)
    glm::vec2 directions[] = {
        {1.0f, 1.0f}, {-1.0f, 1.0f}, {1.0f, -1.0f}, {-1.0f, -1.0f},
        {std::sqrt(2.0f), 0.0f}, {-std::sqrt(2.0f), 0.0f}, {0.0f, std::sqrt(2.0f)}, {0.0f, -std::sqrt(2.0f)}
    };

    for (const auto& direction : directions) {
        std::shared_ptr<EnemyArrow> m_Arrow = std::make_shared<EnemyArrow>();
        m_Arrow->setTarget(shared_from_this());
        m_Arrow->setTarget(m_Giraffe);
        m_Arrow->setWall(m_wall);
        m_Arrow->Start("", direction, "arrow", true); // 使用默認圖片路徑和方向，並設置為反彈
        m_Arrow->Setspeed(4.0f); // 設置箭的速度
        m_Arrows.push_back(m_Arrow);
        this->AddChild(m_Arrow);
    }
}