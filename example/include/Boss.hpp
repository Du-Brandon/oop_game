#pragma  once

#include "Enemy.hpp"
#include "Wall.hpp"

#include <cmath>
#include <vector>
#include <memory>

#include "Enemy.hpp"
#include "hp.hpp"
#include "Wall.hpp"
#include "EnemyArrow.hpp"

class Boss_1_1 : public Enemy , public std::enable_shared_from_this<Enemy> {
public:
    Boss_1_1() = default;
    ~Boss_1_1() override = default;

    void Update() override;
    void Start(glm::vec2 coordinate) override;

    glm::vec2 move() override;
    void shoot() override;


    // std::vector<std::shared_ptr<EnemyArrow>> m_Arrows; // 射出的箭
private:

    float attect_interval = 0.0f; // 攻擊間隔
};

class Boss_1_2 : public Enemy , public std::enable_shared_from_this<Enemy> {
    public:
        Boss_1_2() = default;
        ~Boss_1_2() override = default;
    
        void Update() override;
        void Start(glm::vec2 coordinate) override;
    
        glm::vec2 move() override;
        void shoot() override;
    
    
        // std::vector<std::shared_ptr<EnemyArrow>> m_Arrows; // 射出的箭
    private:
    
        float attect_interval = 0.0f; // 攻擊間隔
    };

class Boss_1_3 : public Enemy , public std::enable_shared_from_this<Enemy> {
    public:
        Boss_1_3() = default;
        ~Boss_1_3() override = default;
    
        void Update() override;
        void Start(glm::vec2 coordinate) override;
    
        glm::vec2 move() override;
        void shoot() override;
    
    
        // std::vector<std::shared_ptr<EnemyArrow>> m_Arrows; // 射出的箭
    private:
    
        float attect_interval = 0.0f; // 攻擊間隔
    };

class Boss_1_4 : public Enemy , public std::enable_shared_from_this<Enemy> {
    public:
        Boss_1_4() = default;
        ~Boss_1_4() override = default;
    
        void Update() override;
        void Start(glm::vec2 coordinate) override;
    
        glm::vec2 move() override;
        void shoot() override;
    
    
        // std::vector<std::shared_ptr<EnemyArrow>> m_Arrows; // 射出的箭
    private:
    
        float attect_interval = 0.0f; // 攻擊間隔
    };


class Boss_2 : public Enemy , public std::enable_shared_from_this<Enemy> {
    public:
        Boss_2() = default;
        ~Boss_2() override = default;
    
        void Update() override;
        void Start(glm::vec2 coordinate) override;
    
        glm::vec2 move() override;
        void shoot() override;
    
        bool summon_enemy_3 = false;
        
    private:

        int count = 0; // 計數器
        int count_max = 550; // 計數器上限
        float attect_interval = 0.0f; // 攻擊間隔

        
        std::vector<std::shared_ptr<EnemyArrow>> m_Arrows; // 射出的箭
        void shoot_random();
    };

class Boss_3 : public Enemy , public std::enable_shared_from_this<Enemy> {
    public:
        Boss_3() = default;
        ~Boss_3() override = default;
    
        void Update() override;
        void Start(glm::vec2 coordinate) override;
    
        glm::vec2 move() override;
        void shoot() override;
    
        // bool summon_enemy_4 = false;
        
    private:

        int count = 0; // 計數器
        int count_max = 355; // 計數器上限
        float attect_interval = 0.0f; // 攻擊間隔

        std::vector<std::shared_ptr<EnemyArrow>> m_Arrows; // 射出的箭

        void shoot_diagonal(); // 米字散射
        
    };