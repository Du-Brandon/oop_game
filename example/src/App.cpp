#include "App.hpp"

#include "log_my.hpp"
#include "Angel.hpp"
#include "Enemy_2.hpp"
#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

#include <iostream>
#include <memory>
#include <ostream>


void App::Start() {
    LOG_TRACE("Start");
    // std::cout << "Start" << std::endl;

    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }

    if (m_Background_bool == false) {
        m_Background->SetBackground("background");
        m_Root.AddChild(m_Background);
        m_Background_bool = true;
    }

    m_Skill_choose->setGiraffe(m_Giraffe); // 只設定 m_Skill_choose
    m_Root.AddChild(m_Skill_choose);       // 只加 m_Skill_choose

    if (Util::Input::IsKeyDown(Util::Keycode::KP_ENTER)) {
        Logger::info("First level");
        wall->Start(180.0f, -180.0f, -464.0f, 267.0f, 32.0f, -19.0f);

        m_Giraffe->Start();
        m_Giraffe->Setwall(wall);

        std::shared_ptr<Enemy_2> m_Enemy2 = std::make_shared<Enemy_2>();
        m_Enemy2->SetDrawable( 
            std::make_shared<Util::Image>("../assets/sprites/enemy.png"));
        m_Enemy2->SetZIndex(5);
        m_Enemy2->Start(glm::vec2(100, 100)); // 初始化敵人的位置
        m_Enemy2->setWall(wall);
    
        m_Enemy->SetDrawable(
            std::make_shared<Util::Image>("../assets/sprites/enemy.png"));
        m_Enemy->SetZIndex(5);
        m_Enemy->Start(glm::vec2(100,100)); // 初始化敵人的位置
        m_Enemy->setWall(wall);
        
        m_Background->SetBackground("test10");

        m_Root.AddChild(m_Giraffe);
        // m_Root.AddChild(m_Cat);
        m_Root.AddChild(m_Enemy);
        m_Root.AddChild(m_Enemy2);

        m_Enemies.push_back(m_Enemy);
        m_Enemies.push_back(m_Enemy2);
        
        m_Ground_Spikes->clear();
        m_Root.AddChild(m_Ground_Spikes);

        m_player_level = player_level::first_level;
        m_CurrentState = State::UPDATE;
        now_level = 1;
    }
    m_Root.Update();
}

void App::Update(){

    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
    
    if (giraffe_level < m_Giraffe->getLevel()) {
        giraffe_level = m_Giraffe->getLevel();
        skill_choose = true;
    }

    for (auto &enemy : m_Enemies) {
        if (auto angel = std::dynamic_pointer_cast<Angel>(enemy)) {
            if (angel->m_Triggered) {
                // 觸發技能選擇界面
                angel_skill_choose = true;
                angel->m_Triggered = false; // 重置觸發狀態
                Logger::info("Angel skill choose triggered.");
            }
        }
    }

    if (skill_choose == false && angel_skill_choose == false) {
        // m_Dark_pic->Disappear();
        
        switch (levelstatus) {
            case levelstatus::normal_level:{
                normal_level_Update();
                break;
            }

            case levelstatus::boss_level:{
                Boss_Update();
                break;
            }
            
        }
    }
    else if (skill_choose == true && angel_skill_choose == false) {
        // m_Dark_pic->Appear();
        m_Skill_choose->SetVisible(true);
        m_Skill_choose->choose_three_skill();
        if (m_Skill_choose->has_clicked_bool()) {
            skill_choose = false;
            m_Skill_choose->SetVisible(false);  // 選擇完後隱藏
        }
    }
    else if (angel_skill_choose == true) {
        // m_Dark_pic->Appear();
        m_Skill_choose->SetVisible(true);
        m_Skill_choose->choose_two_skill();
        if (m_Skill_choose->has_clicked_bool()) {
            angel_skill_choose = false;
            m_Skill_choose->SetVisible(false);  // 選擇完後隱藏
        }
    }

    // 按r測試程式是否正常運行
    if (Util::Input::IsKeyDown(Util::Keycode::R)) {
        Logger::info("R key pressed, restarting level.");
    }

    m_Root.Update();
}

void App::normal_level_Update() {

    if (!m_Giraffe) {
        Logger::error("m_Giraffe is nullptr in Update");
        return;
    }

    if (!wall) {
        Logger::error("wall is nullptr in Update");
        return;
    }

    m_Giraffe->ClearEnemies();

    if (!m_Enemies.empty()) {
        m_Giraffe->SetEnemies(m_Enemies);
    } else {
        Logger::warn("m_Enemies is empty in Update");
    }

    m_Giraffe->Update();
    auto m_Giraffe_pos = m_Giraffe->coordinate();

    if (m_Ground_Spikes->collision_check(m_Giraffe_pos)){
        m_Giraffe->addHP(-1);
        Logger::info("Ground_Spikes collision detected! Giraffe HP: " + std::to_string(m_Giraffe->getHP()));
    }

    for (auto &enemy_it : m_Enemies) {
        if (!enemy_it) {
            Logger::warn("enemy_it is nullptr in Update");
            continue;
        }

        enemy_it->setGiraffe(m_Giraffe);
        enemy_it->Update();
        m_Enemy_pos = enemy_it->coordinate();

        if (glm::distance(m_Giraffe_pos, m_Enemy_pos) < 50 && enemy_it->getVisible()) {
            m_Giraffe->addHP(-enemy_it->getAtk());
            Logger::info("Collision detected! Giraffe HP: " + std::to_string(m_Giraffe->getHP()));
        }

        if (enemy_it->getHP() <= 0) {
            if (enemy_it->getFinal_wish() == "Add player's hp") {
                Logger::info("Adding player's HP");
                m_Giraffe->addHP(50);
                Logger::info("Giraffe HP: " + std::to_string(m_Giraffe->getHP()));
            }
            enemy_it->SetVisible(false);
        }
    }

    for (auto &enemy_it : m_Enemies) {
        if (!enemy_it) {
            Logger::warn("enemy_it is nullptr in Update (visibility check)");
            continue;
        }

        if (enemy_it->getVisible()) {
            is_enemy_empty = false;
            break;
        } else {
            giraffe_exp += enemy_it->getExp_supply();
            enemy_it->setExp_supply(0);
            is_enemy_empty = true;
        }
    }

    m_Giraffe->set_enemy_is_empty(is_enemy_empty);
    if (is_enemy_empty) {
        m_Background->nextbackground(now_level);
        m_Giraffe->setExp(giraffe_exp);
        giraffe_exp = 0;

        if (wall->nextlevel_collision_check(m_Giraffe_pos)) {
            m_player_level = nextLevel(m_player_level);
            Logger::info("Now exp " + std::to_string(static_cast<int>(m_Giraffe->getExp())));
            ValidTask();
        }
    }

    if (m_Giraffe->getHP() <= 0) {
        m_player_level = player_level::end;
        Logger::info("Giraffe HP is 0. Game over.");
        ValidTask();
    }

    
}

void App::Boss_Update() {
    // LOG_TRACE("Boss_Update");

    if (!m_Giraffe) {
        Logger::error("m_Giraffe is nullptr in Boss_Update");
        return;
    }

    if (!wall) {
        Logger::error("wall is nullptr in Boss_Update");
        return;
    }

    m_Giraffe->ClearEnemies();

    if (!m_Enemies.empty()) {
        m_Giraffe->SetEnemies(m_Enemies);
    } else {
        Logger::warn("m_Enemies is empty in Boss_Update");
    }
    if (log){
        Logger::info("m_giraffe->SetEnemies(m_Enemies);");
    }

    m_Giraffe->Update();
    if (log){
        Logger::info("m_giraffe->Update();");
    }

    auto m_Giraffe_pos = m_Giraffe->coordinate();


    for (unsigned i = 0; i < m_Enemies.size(); ++i) {
        // auto enemy_it = m_Enemies.at(i);
        auto enemy_it = m_Enemies[i];
        if (!enemy_it) {
            Logger::warn("enemy_it is nullptr in Boss_Update");
            continue;
        }

        enemy_it->setGiraffe(m_Giraffe);
        enemy_it->Update();
        m_Enemy_pos = enemy_it->coordinate();

        if (glm::distance(m_Giraffe_pos, m_Enemy_pos) < 50 && enemy_it->getVisible()) {
            m_Giraffe->addHP(-enemy_it->getAtk());
            Logger::info("Collision detected! Giraffe HP: " + std::to_string(m_Giraffe->getHP()));
        }

        if (enemy_it->getHP() <= 0 && enemy_it->getVisible()) {
            if (log) {
                Logger::info("Enemy defeated: " + enemy_it->getName());
            }

            if (enemy_it->getFinal_wish() == "Add two Boss_1_2") {
                Logger::info("Spawning two Boss_1_2");
                std::shared_ptr<Boss_1_2> m_Boss_1_2_1 = std::make_shared<Boss_1_2>();
                m_Boss_1_2_1->Start(enemy_it->coordinate());
                m_Boss_1_2_1->setWall(wall);
                m_Enemies.push_back(m_Boss_1_2_1);
                m_Root.AddChild(m_Boss_1_2_1);

                std::shared_ptr<Boss_1_2> m_Boss_1_2_2 = std::make_shared<Boss_1_2>();
                m_Boss_1_2_2->Start(enemy_it->coordinate());
                m_Boss_1_2_2->setWall(wall);
                m_Enemies.push_back(m_Boss_1_2_2);
                m_Root.AddChild(m_Boss_1_2_2);
            } else if (enemy_it->getFinal_wish() == "Add two Boss_1_3") {
                Logger::info("Spawning two Boss_1_3");
                std::shared_ptr<Boss_1_3> m_Boss_1_3_1 = std::make_shared<Boss_1_3>();
                m_Boss_1_3_1->Start(enemy_it->coordinate());
                m_Boss_1_3_1->setWall(wall);
                m_Enemies.push_back(m_Boss_1_3_1);
                m_Root.AddChild(m_Boss_1_3_1);

                std::shared_ptr<Boss_1_3> m_Boss_1_3_2 = std::make_shared<Boss_1_3>();
                m_Boss_1_3_2->Start(enemy_it->coordinate());
                m_Boss_1_3_2->setWall(wall);
                m_Enemies.push_back(m_Boss_1_3_2);
                m_Root.AddChild(m_Boss_1_3_2);

                // 印出 enemies 中所有物件的名稱
                // for (const auto &enemy : m_Enemies) {
                //     Logger::info("Enemy name: " + enemy->getName());
                // }

                Logger::info("Add two Boss_1_3 finish");
            } else if (enemy_it->getFinal_wish() == "Add two Boss_1_4") {
                Logger::info("Spawning two Boss_1_4");
                std::shared_ptr<Boss_1_4> m_Boss_1_4_1 = std::make_shared<Boss_1_4>();
                m_Boss_1_4_1->Start(enemy_it->coordinate());
                m_Boss_1_4_1->setWall(wall);
                m_Enemies.push_back(m_Boss_1_4_1);
                m_Root.AddChild(m_Boss_1_4_1);

                std::shared_ptr<Boss_1_4> m_Boss_1_4_2 = std::make_shared<Boss_1_4>();
                m_Boss_1_4_2->Start(enemy_it->coordinate());
                m_Boss_1_4_2->setWall(wall);
                m_Enemies.push_back(m_Boss_1_4_2);
                m_Root.AddChild(m_Boss_1_4_2);
            } else if (enemy_it->getFinal_wish() == "Add player's hp") {
                Logger::info("Adding player's HP");
                m_Giraffe->addHP(10);
                Logger::info("Giraffe HP: " + std::to_string(m_Giraffe->getHP()));
            }

            if (enemy_it) {
                enemy_it->SetVisible(false);
                Logger::info("Set enemy visibility to false for enemy: " + enemy_it->getName());
            } else {
                Logger::warn("enemy_it is nullptr, cannot set visibility to false.");
                m_CurrentState = State::END;
            }
        }
    }
    if (log) {
        Logger::info("m_Enemies loop finish");
    }

    
    for (auto &enemy_it : m_Enemies) {
        if (!enemy_it) {
            Logger::warn("enemy_it is nullptr in Boss_Update (visibility check)");
            continue;
        }

        if (enemy_it->getVisible()) {
            is_enemy_empty = false;
            break;
        } else {
            giraffe_exp += enemy_it->getExp_supply();
            enemy_it->setExp_supply(0);
            is_enemy_empty = true;
        }
    }
    if (log) {
        Logger::info("m_Enemies loop finish (visibility check)");
    }

    m_Giraffe->set_enemy_is_empty(is_enemy_empty);
    if (is_enemy_empty) {
        m_Background->nextbackground(now_level);
        m_Giraffe->setExp(giraffe_exp);
        giraffe_exp = 0;

        if (wall->nextlevel_collision_check(m_Giraffe_pos)) {
            m_player_level = nextLevel(m_player_level);
            Logger::info("Now exp " + std::to_string(static_cast<int>(m_Giraffe->getExp())));
            ValidTask();
        }
    }

    if (log) {
        Logger::info("m_Giraffe->set_enemy_is_empty(is_enemy_empty);");
    }
    if (m_Giraffe->getHP() <= 0) {
        m_player_level = player_level::end;
        Logger::info("Giraffe HP is 0. Game over.");
        ValidTask();
    }
    if (log) {
        Logger::info("m_Giraffe->getHP() <= 0 check finish");
    }

    
    if (log) {
        Logger::info("m_Root.Update();");
    }


    // press SPACE to toggle demo window
    // if (Util::Input::IsKeyDown(Util::Keycode::SPACE)) {
    //     showDemoWindow = !showDemoWindow;
    // }
    // if (showDemoWindow) {
    //     ImGui::ShowDemoWindow();
    // }
}

void App::End() { // NOLINT(this method will mutate members in the future)
    LOG_TRACE("End");
    
}

void App::removeEnemy() {
    for (auto &enemy_it : m_Enemies) {
        m_Root.RemoveChild(enemy_it);
    }
}



