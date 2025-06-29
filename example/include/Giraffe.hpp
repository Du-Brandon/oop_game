#pragma once

#include <string>
#include <utility>
#include <vector>
#include <chrono>
#include <memory>
#include <tuple>

#include "Arrow.hpp"
#include "Enemy.hpp"
#include "Wall.hpp"
#include "hp.hpp"
#include "Exp.hpp"

#include "pch.hpp" // IWYU pragma: export
#include "Util/Renderer.hpp"
#include "Util/GameObject.hpp"
#include "Util/Text.hpp"



class Arrow;
class Enemy;
class exp_pic;
class Dark_pic;
class GiraffeText;
class Giraffe : public Util::GameObject , public std::enable_shared_from_this<Giraffe> {

public:

    void Start();
    void Update();
    void End(); 
    void ShootArrow(int double_arrow , bool rebound_arrow); // 添加這個方法來射箭
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
    void setAtk_speed(float atk_speed); // 添加這個方法來設置長頸鹿的攻擊速度
    float getAtk_speed() const; // 添加這個方法來獲取長頸鹿的攻擊速度
    void setSpeed(float speed); // 添加這個方法來設置長頸鹿的速度
    void addHP(int hp); // 添加這個方法來增加長頸鹿的血量
    void setHP(int hp); // 添加這個方法來設置長頸鹿的血量
    int getHP() const ; // 添加這個方法來獲取長頸鹿的血量
    void addMaxHP(int max_hp); // 添加這個方法來設置長頸鹿的最大血量
    void setExp(int exp); // 添加這個方法來設置長頸鹿的經驗值
    int getExp() const; // 添加這個方法來獲取長頸鹿的經驗值
    int getLevel() const; // 添加這個方法來獲取長頸鹿的等級

    bool getSkill_rebound_arrow() const { return bool_skill_rebound_arrow; } // 添加這個方法來獲取長頸鹿的技能

    void DrawDarkOverlay(); // 添加這個方法來繪製黑色遮罩
    void set_enemy_is_empty(bool is_empty); // 添加這個方法來設置 enemy_is_empty
    void cleararrow(); // 添加這個方法來清除箭矢

    bool bool_skill_double_arrow = false; // 判斷技能1是否被使用
    int skill_back_arrow_count = 0; 
    void addSkill_double_arrow(); // 添加這個方法來增加箭數量
    bool bool_skill_rebound_arrow = false; // 判斷技能2是否被使用
    bool bool_skill_smart = false; // 判斷技能3是否被使用
    bool bool_skill_angry = false; // 判斷技能憤怒是否被使用
    bool bool_skill_invincible = false; // 判斷技能無敵是否被使用
    int skill_invincible_time_count = 0; // 設置技能無敵的時間計數器
    bool burnarrow = false; // 判斷是否燃燒箭矢
    int right_left_side_arrow = 0 ;
    int incline_arrow = 0 ; 
    

private:

    bool contral_Atk_Speed(); // 添加這個方法來獲取長頸鹿的速度
    std::chrono::high_resolution_clock::time_point start ; // 添加這個成員變數來記錄開始時間
    std::chrono::high_resolution_clock::time_point now ; // 添加這個成員變數來記錄結束時間
    
    int atk = 45 ; // 添加這個成員變數來表示長頸鹿的攻擊力
    float atk_speed = 0.9f; // 添加這個成員變數來表示長頸鹿的攻擊速度
    int m_HP = 250; // 添加這個成員變數來表示長頸鹿的血量
    int max_hp = 250; // 添加這個成員變數來表示長頸鹿的最大血量
    int exp = 0; // 添加這個成員變數來表示長頸鹿的經驗值
    float delta = 0.0f; // 添加這個成員變數來表示長頸鹿的速度

    glm::vec2 &pos = m_Transform.translation; // 長頸鹿的位置
    glm::vec2 &scale = m_Transform.scale; // 長頸鹿的大小
    float &rotation = m_Transform.rotation; // 長頸鹿的旋轉角度

    // skill list
    void skill_double_arrow(); // 技能1
    // void skill_rebound_arrow(); // 技能2
    // void skill_smart(); // 技能3



    // 各技能的布林直 or 參數
        // skill_double_arrow
        std::chrono::high_resolution_clock::time_point arrowCooldown ; // 記錄累積的 delta 時間
        // bool double_arrow_is_shoot = false; // 判斷雙發
        std::tuple<bool,int,int> double_arrow_is_shoot = {false, 0,0}; // 判斷雙發的參數


    // bool Is_move; // 判斷長頸鹿是否移動
    bool anyKeyPressed ; // 判斷是否有按鍵被按下


    std::shared_ptr<Dark_pic> m_Dark_pic = std::make_shared<Dark_pic>(); // 添加這個成員變數來存儲黑色遮罩的指針
    std::shared_ptr<Wall> m_Wall; // 添加這個成員變數來存儲牆的指針
    std::shared_ptr<Enemy> m_Enemy; // 添加這個成員變數來存儲敵人的指針
    std::vector<std::shared_ptr<Enemy>> m_Enemies;
    std::vector<std::shared_ptr<Arrow>> m_Arrows; // 添加這個成員變數來存儲 Arrow 對象
    std::shared_ptr<hp_pic> m_hp_pic = std::make_shared<hp_pic>(); // 添加這個成員變數來存儲血量的指針
    std::shared_ptr<exp_pic> m_exp_pic = std::make_shared<exp_pic>(); // 添加這個成員變數來存儲經驗值的指針
    std::vector<int> m_exp_list = {20, 80, 150, 200, 250, 280, 300, 320, 350, 380, 400, 400,10000}; // 經驗值列表

    std::shared_ptr<GiraffeText> m_Giraffe_atk_Text = std::make_shared<GiraffeText>(); 
    std::shared_ptr<GiraffeText> m_Giraffe_hp_Text = std::make_shared<GiraffeText>(); 
    std::shared_ptr<GiraffeText> m_Giraffe_if_invincible_Text = std::make_shared<GiraffeText>(); 
    std::vector<std::shared_ptr<GiraffeText>> m_GiraffeTexts; // 添加這個成員變數來存儲 GiraffeText 對象

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

class GiraffeText : public Util::GameObject {
public:
    GiraffeText() = default;
    ~GiraffeText() override = default;
    void Start(std::string word, glm::vec2 pos, std::shared_ptr<Giraffe> giraffe = nullptr);
    void Update();
    void end();

private:
    glm::vec2 &pos = m_Transform.translation;
    glm::vec2 &scale = m_Transform.scale;

    std::string m_Word = ""; // 攻擊力顯示的字串
    std::string parameter = "0"; // 攻擊力顯示的參數

    std::string m_Font = "../assets/fonts/wb.ttf";
    int m_Size = 32;
    int level = 1; // 等級
    std::shared_ptr<Util::Text> m_Text; // 用於顯示角色攻擊力，血量，無敵

    std::shared_ptr<Giraffe> giraffe; 
};
