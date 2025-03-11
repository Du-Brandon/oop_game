#include "App.hpp"

#include "Enemy.hpp"
#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

#include <iostream>

#include "GiraffeText.hpp"

void App::Start() {
    LOG_TRACE("Start");
    // std::cout << "Start" << std::endl;

    if (m_Background_bool == false) {
        m_Background->SetBackground("background");
        m_Root.AddChild(m_Background);
        m_Background_bool = true;
    }
    if (Util::Input::IsKeyDown(Util::Keycode::KP_ENTER)) {

        m_Giraffe->Start();

        m_Enemy2->SetDrawable(
            std::make_shared<Util::Image>("../assets/sprites/enemy.png"));
        m_Enemy2->SetZIndex(5);
        m_Enemy2->Start(glm::vec2(100, 100)); // 初始化敵人的位置
    
        m_Enemy->SetDrawable(
            std::make_shared<Util::Image>("../assets/sprites/enemy.png"));
        m_Enemy->SetZIndex(5);
        m_Enemy->Start(glm::vec2(100,100)); // 初始化敵人的位置
        
        m_Background->SetBackground("test");

        m_Root.AddChild(m_Giraffe);
        // m_Root.AddChild(m_Cat);
        m_Root.AddChild(m_Enemy);
        m_Root.AddChild(m_Enemy2);
        m_player_level = player_level::first_level;
        m_CurrentState = State::UPDATE;
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

    // if (Util::Input::IsKeyDown(Util::Keycode::A)) {
    //     LOG_DEBUG("A Down");
    // }

    // if (Util::Input::IsKeyPressed(Util::Keycode::B)) {
    //     LOG_DEBUG("B Pressed. Setting the cursor to (0, 0).");
    //     Util::Input::SetCursorPosition({0.0F, 0.0F});
    //     LOG_DEBUG("Cursor set to {}.", Util::Input::GetCursorPosition());
    // }

    m_Enemy->Update();
    m_Enemy2->Update();
    auto m_Enemy_pos = m_Enemy->coordinate();
    auto m_Enemy2_pos = m_Enemy2->coordinate();
    // m_Giraffe->SetEnemy(m_Enemy);
    m_Giraffe->ClearEnemies();
    m_Giraffe->SetEnemies(m_Enemy);
    m_Giraffe->SetEnemies(m_Enemy2);

    m_Giraffe->Update();
    auto m_Giraffe_pos = m_Giraffe->coordinate();
    
    if (m_Enemy -> getHP() <= 0) {
        m_Enemy->SetVisible(false);
    }

    if (m_Enemy2 -> getHP() <= 0) {
        m_Enemy2->SetVisible(false);
    }

    // m_Cat->Update();
    
    if (!m_Enemy -> getVisible() && !m_Enemy2 -> getVisible()) {
        m_Giraffe->set_enemy_is_empty(true);
    }

    // 碰撞檢測，90為正常參數
    if (glm::distance(m_Giraffe_pos, m_Enemy_pos) < 50 && m_Enemy -> getVisible()|| (glm::distance(m_Giraffe_pos, m_Enemy2_pos) < 50 && m_Enemy2 -> getVisible())) {
        // static int count = 0; //測試碰撞次數
        // std::cout << "Collision detected! " << count << std::endl;
        // count++;
        m_Giraffe->setHP(-1);
        LOG_DEBUG("Collision detected!");
        std::cout << "Giraffe HP: " << m_Giraffe->getHP() << std::endl;
    }

    if (m_Giraffe->getHP() <= 0) {
        m_CurrentState = State::END;
    }



    m_Root.Update();
    ValidTask();
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

    case player_level::end:
        this->End();
        break;

    }
}
