#include "App.hpp"

#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

#include <iostream>

#include "GiraffeText.hpp"

void App::Start() {
    LOG_TRACE("Start");

    m_Giraffe->SetDrawable(
        std::make_shared<Util::Image>("../assets/sprites/sticker.png"));
    m_Giraffe->SetZIndex(6);
    m_Giraffe->Start();
    m_Giraffe->m_Transform.scale = glm::vec2(0.5f, 0.5f); // 將圖片縮小一半

    m_Enemy->SetDrawable(
        std::make_shared<Util::Image>("../assets/sprites/enemy.png"));
    m_Enemy->SetZIndex(5);
    m_Enemy->m_Transform.scale = glm::vec2(0.5f, 0.5f); // 將圖片縮小一半

    // m_Arrow->SetDrawable(
    //     std::make_shared<Util::Image>("../assets/sprites/arrow.png"));
    // m_Arrow->SetZIndex(6);
    // m_Arrow->Start();

    m_Root.AddChild(m_Giraffe);
    m_Root.AddChild(m_Cat);
    m_Root.AddChild(m_Enemy);
    // m_Root.AddChild(m_Arrow);

    m_CurrentState = State::UPDATE;
}

void App::Update() {
    if (Util::Input::IsKeyPressed(Util::Keycode::MOUSE_LB)) {
        LOG_DEBUG("Left button pressed");
    }
    if (Util::Input::IsKeyDown(Util::Keycode::MOUSE_RB)) {
        LOG_DEBUG("Right button down");
    }
    if (Util::Input::IsKeyUp(Util::Keycode::MOUSE_RB)) {
        LOG_DEBUG("Right button up");
    }
    if (Util::Input::IfScroll()) {
        auto delta = Util::Input::GetScrollDistance();
        LOG_DEBUG("Scrolling: x: {}, y: {}", delta.x, delta.y);
    }
    if (Util::Input::IsMouseMoving()) {
        // LOG_DEBUG("Mouse moving! x:{}, y{}", cursorPos.x, cursorPos.y);
    }

    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }

    if (Util::Input::IsKeyDown(Util::Keycode::A)) {
        LOG_DEBUG("A Down");
    }

    if (Util::Input::IsKeyPressed(Util::Keycode::B)) {
        LOG_DEBUG("B Pressed. Setting the cursor to (0, 0).");
        Util::Input::SetCursorPosition({0.0F, 0.0F});
        LOG_DEBUG("Cursor set to {}.", Util::Input::GetCursorPosition());
    }

    m_Giraffe->Update();
    auto m_Giraffe_pos = m_Giraffe->coordinate();
    
    m_Cat->Update();
    
    m_Enemy->Update();
    auto m_Enemy_pos = m_Enemy->coordinate();

    // 碰撞檢測，90為正常參數
    if (m_Giraffe_pos.x >= m_Enemy_pos.x - 90 && m_Giraffe_pos.x <= m_Enemy_pos.x + 90 && m_Giraffe_pos.y >= m_Enemy_pos.y - 90 && m_Giraffe_pos.y <= m_Enemy_pos.y + 90) {
        // static int count = 0; //測試碰撞次數
        // std::cout << "Collision detected! " << count << std::endl;
        // count++;
        LOG_DEBUG("Collision detected!");
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
