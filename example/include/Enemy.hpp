#pragma once 

#include <string>

#include "pch.hpp" // IWYU pragma: export
#include "Util/GameObject.hpp"

class Enemy : public Util::GameObject {
    public:
    Enemy() = default;
    virtual ~Enemy() override = default; // 在 .hpp 文件中聲明虛擬解構元

    virtual void Update() = 0;  
    virtual void Start() = 0;  
    virtual void Start(glm::vec2 coordinate) = 0;  

    virtual glm::vec2 coordinate() const = 0;  
    virtual void move() = 0;
    virtual int getHP() const = 0;  
    virtual void setHP(int hp) = 0;  
    virtual void setAtk(int atk) = 0;  
    virtual int getAtk() const = 0;  
    virtual void setExp_supply(int exp) = 0;  
    virtual int getExp_supply() const = 0;  
    virtual bool getVisible() const = 0;  

protected:
    int m_HP = 100; // 添加這個成員變數來表示敵人的血量
    int m_atk = 10; // 添加這個成員變數來表示敵人的攻擊力
    int exp_supply = 10; // 添加這個成員變數來表示敵人的經驗值

    glm::vec2 &pos = m_Transform.translation; // 敵人的位置
    glm::vec2 &scale = m_Transform.scale; // 敵人的大小
    glm::vec2 dir; // 敵人的移動方向
    float &rotation = m_Transform.rotation; // 敵人的旋轉角度

    glm::vec2 randomMove(char x); // 生成隨機移動方向的方法
};









