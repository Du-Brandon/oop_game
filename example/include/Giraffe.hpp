#ifndef GIRAFFE_HPP
#define GIRAFFE_HPP

#include <utility>
#include <vector>
#include <chrono>
#include <memory>
#include "Arrow.hpp"
#include "Enemy.hpp"
#include "Wall.hpp"
#include "hp.hpp"
#include "Exp.hpp"

#include "pch.hpp" // IWYU pragma: export
#include "Util/Renderer.hpp"
#include "GiraffeText.hpp"
#include "Util/GameObject.hpp"
#include "Util/Text.hpp"



class Arrow;
class Enemy;
class exp_pic;
class Dark_pic;
class Giraffe : public Util::GameObject , public std::enable_shared_from_this<Giraffe> {

public:

    void Update();

    void Start();
    void ShootArrow(bool double_arrow , bool rebound_arrow); // 添加生成 Arrow 的方法
    void SetEnemy(std::shared_ptr<Enemy> enemy); // 添加這個方法來設置 m_Enemy 的指針
    void SetEnemies(std::shared_ptr<Enemy> enemy); // 添加這個方法來設置 m_Enemies 的向量
    void SetEnemies(std::vector<std::shared_ptr<Enemy>> enemies); // 添加這個方法來設置 m_Enemies 的向量
    void Setwall(std::shared_ptr<Wall> wall); // 添加這個方法來設置 m_Wall 的指針
    void ClearEnemies(); // 添加這個方法來清除 m_Enemy 的指針

    glm::vec2 coordinate();

    // 檢查最近的敵人
    std::shared_ptr<Enemy> checkNearestEnemy();


    void setpos(glm::vec2 position); // 添加這個方法來設置長頸鹿的位置
    void setAtk(int atk); // 添加這個方法來設置長頸鹿的攻擊力
    int getAtk() ; // 添加這個方法來獲取長頸鹿的攻擊力
    void setSpeed(float speed); // 添加這個方法來設置長頸鹿的速度
    void setHP(int hp); // 添加這個方法來設置長頸鹿的血量
    int getHP() const ; // 添加這個方法來獲取長頸鹿的血量
    void setExp(int exp); // 添加這個方法來設置長頸鹿的經驗值
    int getExp() const; // 添加這個方法來獲取長頸鹿的經驗值
    int getLevel() const; // 添加這個方法來獲取長頸鹿的等級

    bool getSkill_rebound_arrow() const { return bool_skill_rebound_arrow; } // 添加這個方法來獲取長頸鹿的技能

    void DrawDarkOverlay(); // 添加這個方法來繪製黑色遮罩
    void set_enemy_is_empty(bool is_empty); // 添加這個方法來設置 enemy_is_empty
    void cleararrow(); // 添加這個方法來清除箭矢

    bool bool_skill_double_arrow = false; // 判斷技能1是否被使用
    bool bool_skill_rebound_arrow = false; // 判斷技能2是否被使用
    bool bool_skill_smart = false; // 判斷技能3是否被使用
    bool bool_skill_angry = false; // 判斷技能4是否被使用

private:

    bool contral_Atk_Speed(); // 添加這個方法來獲取長頸鹿的速度
    std::chrono::high_resolution_clock::time_point start ; // 添加這個成員變數來記錄開始時間
    std::chrono::high_resolution_clock::time_point now ; // 添加這個成員變數來記錄結束時間
    
    int atk = 100; // 添加這個成員變數來表示長頸鹿的攻擊力
    float atk_speed = 0.9f; // 添加這個成員變數來表示長頸鹿的攻擊速度
    int m_HP = 150; // 添加這個成員變數來表示長頸鹿的血量
    int max_hp = 150; // 添加這個成員變數來表示長頸鹿的最大血量
    int exp = 0; // 添加這個成員變數來表示長頸鹿的經驗值
    float delta = 0.0f; // 添加這個成員變數來表示長頸鹿的速度

    glm::vec2 &pos = m_Transform.translation; // 長頸鹿的位置
    glm::vec2 &scale = m_Transform.scale; // 長頸鹿的大小
    float &rotation = m_Transform.rotation; // 長頸鹿的旋轉角度

    // skill list
    void judge_skill(); // 判斷技能
    void skill_double_arrow(); // 技能1
    // void skill_rebound_arrow(); // 技能2
    // void skill_smart(); // 技能3



    // 各技能的布林直 or 參數
        // skill_double_arrow
        std::chrono::high_resolution_clock::time_point arrowCooldown ; // 記錄累積的 delta 時間
        bool double_arrow_is_shoot = false; // 判斷技能1是否被使用


    // bool Is_move; // 判斷長頸鹿是否移動
    bool anyKeyPressed ; // 判斷是否有按鍵被按下

    std::shared_ptr<GiraffeText> m_GiraffeText;
    std::shared_ptr<Dark_pic> m_Dark_pic = std::make_shared<Dark_pic>(); // 添加這個成員變數來存儲黑色遮罩的指針
    std::shared_ptr<Wall> m_Wall; // 添加這個成員變數來存儲牆的指針
    std::shared_ptr<Enemy> m_Enemy; // 添加這個成員變數來存儲敵人的指針
    std::vector<std::shared_ptr<Enemy>> m_Enemies;
    std::vector<std::shared_ptr<Arrow>> m_Arrows; // 添加這個成員變數來存儲 Arrow 對象
    std::shared_ptr<hp_pic> m_hp_pic = std::make_shared<hp_pic>(); // 添加這個成員變數來存儲血量的指針
    std::shared_ptr<exp_pic> m_exp_pic = std::make_shared<exp_pic>(); // 添加這個成員變數來存儲經驗值的指針
    std::vector<int> m_exp_list = {20, 80, 150, 220, 310, 400}; // 經驗值列表

    bool enemy_is_empty = false; // 判斷敵人是否存在
};

class Dark_pic : public Util::GameObject {
public:
    Dark_pic() = default;
    ~Dark_pic() override = default;
    void Start() ;
    void Appear() ;
    void Disappear();

private:
    glm::vec2 &pos = m_Transform.translation; // 
    glm::vec2 &scale = m_Transform.scale; // 
};

#endif // GIRAFFE_HPP
