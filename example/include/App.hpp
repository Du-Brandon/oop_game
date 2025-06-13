#pragma once

/* */
// #define TRACY_ENABLE
// #include "../public/tracy/Tracy.hpp"

#include <memory>
#include "background.hpp"
#include "pch.hpp" // IWYU pragma: export

#include "Util/Renderer.hpp"

#include "Cat.hpp"
#include "Wall.hpp"
#include "Ground_Spikes.hpp"
#include "Giraffe.hpp"
#include "Boss.hpp"
#include "Enemy.hpp"
#include "Enemy_1.hpp"
#include "Enemy_2.hpp"
#include "Enemy_3.hpp"
#include "Enemy_4.hpp"
#include "Enemy_5.hpp"
#include "Enemy_6.hpp"
#include "Enemy_7.hpp"
#include "Angel.hpp"
#include "Arrow.hpp"
#include "Skill.hpp"

#include <glm/fwd.hpp>
#include <string>
#include <vector>

class App {
public:
    enum class State {
        START,
        UPDATE,
        END,
    };

    State GetCurrentState() const { return m_CurrentState; }

    void Start();
    void Update();
    void normal_level_Update();
    void Boss_Update();
    void End(); // NOLINT(readability-convert-member-functions-to-static)

private:
void ValidTask();

void InitializeEnemy_1(glm::vec2 coordinate , int hp = 0);
void InitializeEnemy_2(glm::vec2 coordinate , int hp = 0);
void InitializeEnemy_3(glm::vec2 coordinate , int hp = 0 , int exp = 0);
void InitializeEnemy_4(glm::vec2 coordinate , int hp = 0);
void InitializeEnemy_5(glm::vec2 coordinate , int hp = 0);
void InitializeEnemy_6(glm::vec2 coordinate , int hp = 0);
void InitializeEnemy_7(glm::vec2 coordinate , int hp = 0);

private:
    // log or not

    bool log = false; // 是否開啟log

    enum class levelstatus {
        normal_level,
        boss_level,
        win
    };

    enum class player_level  {
        lobby,
        first_level,
        // twenty_fourth_level,
        // twenty_fifth_level,
        second_level,
        third_level,
        fourth_level,
        fifth_level,
        sixth_level,
        seventh_level,
        eighth_level,
        ninth_level,
        tenth_level,
        eleventh_level,
        twelfth_level,
        thirteenth_level,
        fourteenth_level,
        fifteenth_level,
        sixteenth_level,
        seventeenth_level,
        eighteenth_level,
        nineteenth_level,
        twenty_level,
        twenty_first_level,
        twenty_second_level,
        twenty_third_level,
        twenty_fourth_level,
        twenty_fifth_level,
        win_end,
        end
    };

    inline player_level nextLevel(player_level current) {
        // 將 enum class 轉換為整數
        int next = static_cast<int>(current) + 1;
    
        // 確保不超出範圍
        if (next >= static_cast<int>(player_level::end)) {
            return player_level::end; // 如果超出範圍，返回最後一個值
        }
    
        // 將整數轉回 enum class
        return static_cast<player_level>(next);
    }

    bool contains(const std::string& text, const std::string& keyword) {
        return text.find(keyword) != std::string::npos;
    }

    levelstatus levelstatus = levelstatus::normal_level; // 判斷當前是普通關卡還是boss關卡
    State m_CurrentState = State::START;
    player_level m_player_level = player_level::lobby;
    int now_level = 0;

    std::shared_ptr<BackgroundImage> m_Background = std::make_shared<BackgroundImage>();
    bool m_Background_bool = false; // 判斷背景是否已經加載
    bool is_enemy_empty = false; // 判斷敵人是否為空
    std::shared_ptr<Giraffe> m_Giraffe = std::make_shared<Giraffe>();
    std::shared_ptr<Dark_pic> m_Dark_pic = std::make_shared<Dark_pic>();
    std::shared_ptr<Skill_choose> m_Skill_choose = std::make_shared<Skill_choose>();
    int giraffe_exp = 0;
    int giraffe_level = 0;

    std::shared_ptr<Cat> m_Cat = std::make_shared<Cat>();
    std::shared_ptr<Wall> wall = std::make_shared<Wall>();
    std::shared_ptr<Vecter_Ground_Spikes> m_Ground_Spikes = std::make_shared<Vecter_Ground_Spikes>();
    std::shared_ptr<Enemy_1> m_Enemy = std::make_shared<Enemy_1>();

    std::vector<std::shared_ptr<Enemy>> m_Enemies;
    glm::vec2 m_Enemy_pos;
    std::shared_ptr<Arrow> m_Arrow = std::make_shared<Arrow>();
    // std::vector<std::shared_ptr<Arrow>> m_Arrows;
    bool skill_choose = false;
    bool angel_skill_choose = false;

    void removeEnemy();
    Util::Renderer m_Root;

    bool showDemoWindow = true;
};


