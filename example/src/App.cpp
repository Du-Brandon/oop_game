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
        
        m_player_level = player_level::first_level;
        m_CurrentState = State::UPDATE;
        now_level = 1;
    }
    m_Root.Update();
}

void App::Update() {
    // if (Util::Input::IsKeyPressed(Util::Keycode::MOUSE_LB)) {
    //     LOG_DEBUG("Left button pressed");
    // }
    // if (Util::Input::IsKeyDown(Util::Keycode::MOUSE_RB)) {
    //     LOG_DEBUG("Right button down");
    // }
    // if (Util::Input::IsKeyUp(Util::Keycode::MOUSE_RB)) {
    //     LOG_DEBUG("Right button up");
    // }
    // if (Util::Input::IfScroll()) {
    //     auto delta = Util::Input::GetScrollDistance();
    //     LOG_DEBUG("Scrolling: x: {}, y: {}", delta.x, delta.y);
    // }
    if (Util::Input::IsMouseMoving()) {
        // LOG_DEBUG("Mouse moving! x:{}, y{}", cursorPos.x, cursorPos.y);
    }

    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }

    m_Giraffe->ClearEnemies();

    m_Giraffe->SetEnemies(m_Enemies);

    m_Giraffe->Update();
    auto m_Giraffe_pos = m_Giraffe->coordinate();
    
    for (auto &enemy_it : m_Enemies) {
        if (Util::Input::IsKeyDown(Util::Keycode::R)){
            Logger::info("running");
            std::cout << "running"<<std::endl;
        }
        enemy_it->setGiraffe(m_Giraffe);
        enemy_it->Update();
        m_Enemy_pos = (enemy_it->coordinate());
        if (glm::distance(m_Giraffe_pos, m_Enemy_pos) < 50 && enemy_it->getVisible()) {
            m_Giraffe->setHP(-enemy_it->getAtk());
            LOG_DEBUG("Collision detected!");
            std::cout << "Giraffe HP: " << m_Giraffe->getHP() << std::endl;
        }


        if (enemy_it->getHP() <= 0) {
            enemy_it->SetVisible(false);
            // m_Enemies.erase(std::remove(m_Enemies.begin(), m_Enemies.end(), enemy_it), m_Enemies.end());
        }
    }
    // m_Cat->Update();
    
    for (auto &enemy_it : m_Enemies) {
        if (enemy_it->getVisible()) {
            is_enemy_empty = false;
            break;
        } else {
            giraffe_exp += enemy_it->getExp_supply();
            enemy_it -> setExp_supply(0);
            is_enemy_empty = true;
        }
    
    }
    m_Giraffe->set_enemy_is_empty(is_enemy_empty);
    if (is_enemy_empty) {
        
        m_Background->nextbackground(now_level);
        m_Giraffe -> setExp(giraffe_exp);
        giraffe_exp = 0;
        if (wall->nextlevel_collision_check(m_Giraffe_pos)) {
            // m_player_level = player_level::second_level; 
            m_player_level = nextLevel(m_player_level);
            std::cout << "m_player_level: " << m_Giraffe->getExp() << std::endl;
            ValidTask();
        }
    }

    // // 碰撞檢測，90為正常參數
    // if (glm::distance(m_Giraffe_pos, m_Enemy_pos) < 50 && m_Enemy -> getVisible()|| (glm::distance(m_Giraffe_pos, m_Enemy2_pos) < 50 && m_Enemy2 -> getVisible())) {
    //     // static int count = 0; //測試碰撞次數
    //     // std::cout << "Collision detected! " << count << std::endl;
    //     // count++;
    //     m_Giraffe->setHP(-1);
    //     LOG_DEBUG("Collision detected!");
    //     std::cout << "Giraffe HP: " << m_Giraffe->getHP() << std::endl;
    // }

    if (m_Giraffe->getHP() <= 0) {
        m_player_level = player_level::end;
        ValidTask();
    }



    m_Root.Update();

    // press SPACE to toggle demo window
    if (Util::Input::IsKeyDown(Util::Keycode::SPACE)) {
        showDemoWindow = !showDemoWindow;
    }
    if (showDemoWindow) {
        ImGui::ShowDemoWindow();
    }
}

void App::Boss_Update() {
    LOG_TRACE("Boss_Update");


    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }

    m_Giraffe->ClearEnemies();

    m_Giraffe->SetEnemies(m_Enemies);

    m_Giraffe->Update();
    auto m_Giraffe_pos = m_Giraffe->coordinate();
    
    for (auto &enemy_it : m_Enemies) {
        if (Util::Input::IsKeyDown(Util::Keycode::R)){
            std::cout << "running"<<std::endl;
        }
        enemy_it->setGiraffe(m_Giraffe);
        enemy_it->Update();
        m_Enemy_pos = (enemy_it->coordinate());
        if (glm::distance(m_Giraffe_pos, m_Enemy_pos) < 50 && enemy_it->getVisible()) {
            m_Giraffe->setHP(-enemy_it->getAtk());
            LOG_DEBUG("Collision detected!");
            std::cout << "Giraffe HP: " << m_Giraffe->getHP() << std::endl;
        }


        if (enemy_it->getHP() <= 0 && enemy_it->getVisible()) {
            if(enemy_it->getFinal_wish() == "Add two Boss_1_2") {
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
            }
            else if (enemy_it->getFinal_wish() == "Add two Boss_1_3") {
                std::cout << "Add two Boss_1_3" << std::endl;
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

                // 印出enemies中所有物件的名稱
                for (const auto& enemy : m_Enemies) {
                    std::cout << "Enemy name: " << enemy->getName() << std::endl;
                }

                std::cout << "Add two Boss_1_3 finish" << std::endl;
            
            }

            enemy_it->SetVisible(false);

            // m_Enemies.erase(std::remove(m_Enemies.begin(), m_Enemies.end(), enemy_it), m_Enemies.end());
        }
    }
    
    for (auto &enemy_it : m_Enemies) {
        if (enemy_it != nullptr) {
            if (enemy_it->getVisible()) {
                is_enemy_empty = false;
                break;
            } else {
                giraffe_exp += enemy_it->getExp_supply();
                enemy_it -> setExp_supply(0);
                is_enemy_empty = true;
            }
        }
        else {
            Logger::info("enemy_it is nullptr in judge enemy hp");
            is_enemy_empty = true;
        }
    }
    
    m_Giraffe->set_enemy_is_empty(is_enemy_empty);
    if (is_enemy_empty) {
        
        m_Background->nextbackground(now_level);
        m_Giraffe -> setExp(giraffe_exp);
        giraffe_exp = 0;
        if (wall->nextlevel_collision_check(m_Giraffe_pos)) {
            m_player_level = nextLevel(m_player_level);
            std::cout << "m_player_level: " << m_Giraffe->getExp() << std::endl;
            ValidTask();
        }
    }

    if (m_Giraffe->getHP() <= 0) {
        m_player_level = player_level::end;
        ValidTask();
    }

    m_Root.Update();

    // press SPACE to toggle demo window
    if (Util::Input::IsKeyDown(Util::Keycode::SPACE)) {
        showDemoWindow = !showDemoWindow;
    }
    if (showDemoWindow) {
        ImGui::ShowDemoWindow();
    }

}

void App::End() { // NOLINT(this method will mutate members in the future)
    LOG_TRACE("End");
    
}

void App::removeEnemy() {
    for (auto &enemy_it : m_Enemies) {
        m_Root.RemoveChild(enemy_it);
    }
}


void App::ValidTask() {
    LOG_TRACE("ValidTask");
    switch (m_player_level) {
    case player_level::lobby:
        m_Background->SetBackground("background");
        LOG_DEBUG("lobby");
        break;

    case player_level::first_level:
        LOG_DEBUG("first_level");
        break;
    
    case player_level::second_level:{
        LOG_DEBUG("second_level");
        now_level = 2;
        m_Background->nextbackground(now_level);
        this->removeEnemy();
        m_Enemies.clear();

        wall->Start(192.0f, -192.0f, -465.0f, 267.0f, 32.0f, -19.0f);
        wall->setwall(glm::vec2 (-470.36f, 44.0f) , glm::vec2(-305.836f , 200.584f));
        wall->setwall(glm::vec2 (-470.03f, -191.562f) , glm::vec2(-305.101f , -38.670f));
        wall->setwall(glm::vec2 (-134.625f,60.9083f) , glm::vec2(-90.1393f , 162.386f));
        wall->setwall(glm::vec2 (-134.625f,-163.9083f) , glm::vec2(-90.1393f , -64.2383f));                   

        std::shared_ptr<Enemy_2> m_Enemy3 = std::make_shared<Enemy_2>();
        m_Enemy3->SetDrawable(
            std::make_shared<Util::Image>("../assets/sprites/enemy.png"));
        m_Enemy3->SetZIndex(5);
        m_Enemy3->Start(glm::vec2(144, 116)); // 初始化敵人的位置
        m_Enemy3->setWall(wall);
        m_Enemies.push_back(m_Enemy3);
        m_Root.AddChild(m_Enemy3);
        
        std::shared_ptr<Enemy_2> m_Enemy4 = std::make_shared<Enemy_2>();
        m_Enemy4->SetDrawable(
            std::make_shared<Util::Image>("../assets/sprites/enemy.png"));
        m_Enemy4->SetZIndex(5);
        m_Enemy4->Start(glm::vec2(144, -116)); // 初始化敵人的位置
        m_Enemy4->setWall(wall);
        m_Enemies.push_back(m_Enemy4);
        m_Root.AddChild(m_Enemy4);

        std::shared_ptr<Enemy_2> m_Enemy5 = std::make_shared<Enemy_2>();
        m_Enemy5->SetDrawable(
            std::make_shared<Util::Image>("../assets/sprites/enemy.png"));
        m_Enemy5->SetZIndex(5);
        m_Enemy5->setHP(100);
        m_Enemy5->Start(glm::vec2(250, 0)); // 初始化敵人的位置
        m_Enemy5->setWall(wall);
        m_Enemies.push_back(m_Enemy5);
        m_Root.AddChild(m_Enemy5);
        
        giraffe_exp = 0;
        m_Giraffe -> setpos(glm::vec2(-420, 0));
        m_Giraffe -> Setwall(wall);

        is_enemy_empty = false;
        break;
    }
    case player_level ::third_level:{
        LOG_DEBUG("third_level");
        now_level = 3;
        m_Background->nextbackground(now_level);
        this->removeEnemy();
        m_Enemies.clear();

        wall->clear();
        wall->Start(192.0f, -192.0f, -465.0f, 267.0f, 32.0f, -19.0f);
        wall->setwall(glm::vec2 (-389.86f, 91.006f) , glm::vec2(-153.184f , 118.659f));
        wall->setwall(glm::vec2 (-74.8f, 93.42f) , glm::vec2(167.101f , 118.670f));
        wall->setwall(glm::vec2 (-399.625f,-122.9083f) , glm::vec2(-143.606f , -88.7307f));
        wall->setwall(glm::vec2 (-74.625f,-122.9083f) , glm::vec2(169.1393f , -88.7307f));                   

        std::shared_ptr<Enemy_3> m_Enemy6 = std::make_shared<Enemy_3>();
        m_Enemy6->SetDrawable(
            std::make_shared<Util::Image>("../assets/sprites/enemy.png"));
        m_Enemy6->SetZIndex(5);
        m_Enemy6->Start(glm::vec2(226, 145)); // 初始化敵人的位置
        m_Enemy6->setWall(wall);
        m_Enemies.push_back(m_Enemy6);
        m_Root.AddChild(m_Enemy6);
        
        std::shared_ptr<Enemy_3> m_Enemy7 = std::make_shared<Enemy_3>();
        m_Enemy7->SetDrawable(
            std::make_shared<Util::Image>("../assets/sprites/enemy.png"));
        m_Enemy7->SetZIndex(5);
        m_Enemy7->Start(glm::vec2(226, -140)); // 初始化敵人的位置
        m_Enemy7->setWall(wall);
        m_Enemies.push_back(m_Enemy7);
        m_Root.AddChild(m_Enemy7);
        
        std::shared_ptr<Enemy_3> m_Enemy8 = std::make_shared<Enemy_3>();
        m_Enemy8->SetDrawable(
            std::make_shared<Util::Image>("../assets/sprites/enemy.png"));
        m_Enemy8->SetZIndex(5);
        m_Enemy8->Start(glm::vec2(-289, -156)); // 初始化敵人的位置
        m_Enemy8->setWall(wall);
        m_Enemies.push_back(m_Enemy8);
        m_Root.AddChild(m_Enemy8);

        std::shared_ptr<Enemy_3> m_Enemy9 = std::make_shared<Enemy_3>();
        m_Enemy9->SetDrawable(
            std::make_shared<Util::Image>("../assets/sprites/enemy.png"));
        m_Enemy9->SetZIndex(5);
        m_Enemy9->Start(glm::vec2(-289, 156)); // 初始化敵人的位置
        m_Enemy9->setWall(wall);
        m_Enemies.push_back(m_Enemy9);
        m_Root.AddChild(m_Enemy9);


        giraffe_exp = 0;
        m_Giraffe -> setpos(glm::vec2(-420, 0));
        m_Giraffe -> Setwall(wall);

        is_enemy_empty = false;
        break;
    }

    case player_level::fourth_level:{
        LOG_DEBUG("fourth_level");
        now_level = 4;
        m_Background->nextbackground(now_level);
        this->removeEnemy();
        m_Enemies.clear();

        wall->clear();
        wall->Start(192.0f, -192.0f, -465.0f, 267.0f, 32.0f, -19.0f);
        wall->setwall(glm::vec2 (-398.86f, 73.006f) , glm::vec2(-149.116f , 121.659f));
        wall->setwall(glm::vec2 (-398.523f, -131.287f) , glm::vec2(-364.459f , 124.414f));
        wall->setwall(glm::vec2 (-398.883f,-124.099f) , glm::vec2(-146.449f , -52.8387f));
        
        wall->setwall(glm::vec2 (-35.7017f,72.0359f) , glm::vec2(210.873f , 123.596f));                
        wall->setwall(glm::vec2 (166.669f,-122.415f) , glm::vec2(211.375f , 123.596f));                
        wall->setwall(glm::vec2 (-40.2019f,-123.842f) , glm::vec2(210.154f , -63.2669f));                

        std::shared_ptr<Enemy_3> m_Enemy10 = std::make_shared<Enemy_3>();
        m_Enemy10->SetDrawable(
            std::make_shared<Util::Image>("../assets/sprites/enemy.png"));
        m_Enemy10->SetZIndex(5);
        m_Enemy10->Start(glm::vec2(237, 157)); // 初始化敵人的位置
        m_Enemy10->setWall(wall);
        m_Enemies.push_back(m_Enemy10);
        m_Root.AddChild(m_Enemy10);
        
        std::shared_ptr<Enemy_3> m_Enemy11 = std::make_shared<Enemy_3>();
        m_Enemy11->SetDrawable(
            std::make_shared<Util::Image>("../assets/sprites/enemy.png"));
        m_Enemy11->SetZIndex(5);
        m_Enemy11->Start(glm::vec2(237, -162)); // 初始化敵人的位置
        m_Enemy11->setWall(wall);
        m_Enemies.push_back(m_Enemy11);
        m_Root.AddChild(m_Enemy11);

        std::shared_ptr<Enemy_2> m_Enemy12 = std::make_shared<Enemy_2>();
        m_Enemy12->SetDrawable(
            std::make_shared<Util::Image>("../assets/sprites/enemy.png"));  
        m_Enemy12->SetZIndex(5);
        m_Enemy12->Start(glm::vec2(59.96f, 5.513f)); // 初始化敵人的位置
        m_Enemy12->setWall(wall);
        m_Enemies.push_back(m_Enemy12);
        m_Root.AddChild(m_Enemy12);
        
        giraffe_exp = 0;
        m_Giraffe -> setpos(glm::vec2(-500, 0));
        m_Giraffe -> Setwall(wall);

        is_enemy_empty = false;
        break;
    }

    case player_level::fifth_level:{
        LOG_DEBUG("fifth_level");
        now_level = 5;
        m_Background->nextbackground(now_level);
        this->removeEnemy();
        m_Enemies.clear();

        wall->clear();
        wall->Start(192.0f, -192.0f, -465.0f, 267.0f, 32.0f, -19.0f);
        wall->setwall(glm::vec2 (-460.86f, 83.006f) , glm::vec2(267.116f , 125.659f));
        wall->setwall(glm::vec2 (-462.523f, -119.287f) , glm::vec2(267.459f , -85.414f));
        
        std::shared_ptr<Angel> m_Angel = std::make_shared<Angel>();
        m_Angel->SetDrawable(
            std::make_shared<Util::Image>("../assets/sprites/angel.png"));
        m_Angel->SetZIndex(10);
        m_Angel->Start(glm::vec2(200, 0)); // 初始化敵人的位置
        m_Angel->setWall(wall);
        m_Enemies.push_back(m_Angel);
        m_Root.AddChild(m_Angel);

        m_Giraffe -> setpos(glm::vec2(-420, 0));
        m_Giraffe -> Setwall(wall);

        giraffe_exp = 0;
        is_enemy_empty = false;
        break;
    }

    case player_level::tenth_level:{
        LOG_DEBUG("tenth_level");
        m_CurrentState = State::BOSSUPDATE;
        now_level = 6;
        m_Background->nextbackground(now_level);
        this->removeEnemy();
        m_Enemies.clear();

        wall->clear();
        wall->Start(192.0f, -192.0f, -465.0f, 267.0f, 32.0f, -19.0f);
        // wall->setwall(glm::vec2 (-460.86f, 83.006f) , glm::vec2(267.116f , 125.659f));
        // wall->setwall(glm::vec2 (-462.523f, -119.287f) , glm::vec2(267.459f , -85.414f));
        
        std::shared_ptr<Boss_1_1> m_Boss_1_1 = std::make_shared<Boss_1_1>();
        m_Boss_1_1->Start();
        m_Boss_1_1->setWall(wall);
        m_Enemies.push_back(m_Boss_1_1);
        m_Root.AddChild(m_Boss_1_1);    

        std::cout << "m_Boss_1_1 finish" << std::endl;
        m_Giraffe -> setpos(glm::vec2(-420, 0));
        std::cout << "m_Giraffe set finish" << std::endl;
        m_Giraffe -> Setwall(wall);

        is_enemy_empty = false;
        break;
    }

    case player_level::end:
        
        this->End();
        m_CurrentState = State::END;
        break;

    }
}
