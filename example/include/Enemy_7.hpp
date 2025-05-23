#pragma once

#include <Util/GameObject.hpp>
#include <cmath>
#include <vector>
#include <memory>

#include "Enemy.hpp"
#include "Wall.hpp"
#include "EnemyArrow.hpp"

class Enemy_7_attack;
class Enemy_7 : public Enemy , public std::enable_shared_from_this<Enemy> {
public:
    Enemy_7() = default;
    ~Enemy_7() override = default;

    void Update() override;
    void Start(glm::vec2 coordinate) override;

    glm::vec2 move() override;
    void shoot() override;
private:
    int atk_speed = 270;
    int count = 0; // 計數器
    bool decide_dir = false; // 判斷是否要改變方向
    
    std::vector<std::shared_ptr<EnemyArrow>> m_Arrows; // 射出的箭

    float attact_interval = 0.0f; // 攻擊間隔
    int shoot_count = 0; // 計數器

    std::shared_ptr<Enemy_7_attack> m_attack = std::make_shared<Enemy_7_attack>(); // 攻擊的箭
    
};

class Enemy_7_attack : public Util::GameObject{
public:
    Enemy_7_attack() = default;
    ~Enemy_7_attack() override = default;

    void Start();
    void run(glm::vec2 enemy_pos);
    void End();
    void Set_giraffe_pos(glm::vec2 giraffe_pos);
    void Set_enemy_pos(glm::vec2 enemy_pos);

private:
    glm::vec2 giraffe_pos = {0, 0}; // 長頸鹿的位置
    glm::vec2 enemy_pos = {0, 0}; // 敵人的位置
    glm::vec2 &pos = m_Transform.translation; // 敵人的位置
    glm::vec2 &scale = m_Transform.scale; // 敵人的大小
    float &rotation = m_Transform.rotation; // 敵人的旋轉角度

    int count = 0; // 計數器
};
