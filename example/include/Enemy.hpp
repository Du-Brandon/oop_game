#pragma once 

#include <string>

#include "pch.hpp" // IWYU pragma: export
#include "Util/GameObject.hpp"

class Enemy : public Util::GameObject {
public:
    Enemy() = default;
    ~Enemy() override; // 在 .hpp 文件中聲明解構元
    void Update();
    void Start();
    void Start(glm::vec2 coordinate); // 添加這個方法來初始化敵人的位置
    

    glm::vec2 coordinate();
    int getHP() const; // 添加這個方法來獲取敵人的血量
    void setHP(int hp); // 添加這個方法來設置敵人的血量
    void setAtk(int atk); // 添加這個方法來設置敵人的攻擊力
    int getAtk() const; // 添加這個方法來獲取敵人的攻擊力
    void setExp_supply(int exp); // 添加這個方法來設置敵人的經驗值
    int getExp_supply() const; // 添加這個方法來獲取敵人的經驗值
    bool getVisible() const; // 添加這個方法來獲取敵人是否存在

private:
    // bool &IfExist = m_Visible; // 添加這個成員變數來表示敵人是否存在s
    int m_HP = 100; // 添加這個成員變數來表示敵人的血量
    int m_atk = 10; // 添加這個成員變數來表示敵人的攻擊力
    int exp_supply = 10; // 添加這個成員變數來表示敵人的經驗值

    glm::vec2 &pos = m_Transform.translation; // 敵人的位置
    glm::vec2 &scale = m_Transform.scale; // 敵人的大小
    glm::vec2 dir; // 敵人的移動方向
    float &rotation = m_Transform.rotation; // 敵人的旋轉角度

    glm::vec2 randomMove(char x); // 生成隨機移動方向的方法
};










