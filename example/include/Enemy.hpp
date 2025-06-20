#pragma once 

#include "Wall.hpp"
#include "Giraffe.hpp"
#include "hp.hpp"

#include <glm/fwd.hpp>
#include <memory>
#include <string>

#include "pch.hpp" // IWYU pragma: export
#include "Util/GameObject.hpp"
#include "Util/Image.hpp"


// class Wall;
class Giraffe;
class Enemy : public Util::GameObject {
    public:
    Enemy() = default;
    virtual ~Enemy() override = default; // 在 .hpp 文件中聲明虛擬解構元
    
    virtual void Start(glm::vec2 coordinate) = 0;  
    virtual void Update() = 0;  
    void setWall(std::shared_ptr<Wall> wall); // 添加這個方法來設置 m_wall 的指針
    void setGiraffe(glm::vec2 giraffe_pos); // 添加這個方法來設置 m_Giraffe_pos 的值
    void setGiraffe(std::shared_ptr<Giraffe> giraffe); // 添加這個方法來設置 m_Giraffe 的指針

    glm::vec2 coordinate() ;  
    virtual glm::vec2 move() = 0;
    virtual void shoot() = 0;

    
    int getHP()const;  
    void setHP(int hp);
    void set_MaxHP(int hp) ;  
    void setAtk(int atk);  
    int getAtk() const;  
    void setExp_supply(int exp);  
    int getExp_supply() const;  
    void setName(std::string name);
    std::string getName() const;
    std::string getFinal_wish() const;
    virtual bool getVisible() const;  

    bool isburning() const { return burning; } // 添加這個方法來檢查是否燃燒
    void setburning(bool burn) { burning = burn; } // 添加這個方法來設置是否燃燒

    virtual bool isAngel() const { return false; } // 添加這個方法來檢查是否為天使

protected:
    int m_HP = 100; // 添加這個成員變數來表示敵人的血量
    int m_MaxHP = 100; // 添加這個成員變數來表示敵人的最大血量
    int m_atk = 1; // 添加這個成員變數來表示敵人的攻擊力
    int exp_supply = 10; // 添加這個成員變數來表示敵人的經驗值
    float move_speed = 10.0f; 
    std::string name = ""; // 敵人的名稱
    std::string final_wish = ""; // 敵人的最終願望

    glm::vec2 &pos = m_Transform.translation; // 敵人的位置
    glm::vec2 &scale = m_Transform.scale; // 敵人的大小
    glm::vec2 dir; // 敵人的移動方向
    float &rotation = m_Transform.rotation; // 敵人的旋轉角度
    glm::vec2 Giraffe_pos; // 長頸鹿的位置
    std::shared_ptr<Giraffe> m_Giraffe; // 長頸鹿的指針
    std::shared_ptr<Wall> m_wall; // 敵人的碰撞邊界
    std::shared_ptr<hp_pic> m_hp_pic = std::make_shared<hp_pic>(); // 敵人的血量
    
    bool burning = false; // 是否燃燒
    int burning_clock = 0; // 燃燒時間

    glm::vec2 randomMove(char x); // 生成隨機移動方向的方法
    void is_burning(); // 判斷是否燃燒的方法
    void enemy_hp_start(); 
    void enemy_hp_update();
};









