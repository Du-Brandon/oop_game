#include "Button.hpp"
#include "log_my.hpp"

#include "Util/Image.hpp"
#include "Util/Input.hpp"

// 按鈕參考別組

void Button::Start( const std::string& name, 
                    const std::string& imagePath, 
                    const OnClickCallback& callback,
                    glm::vec2 left_bottom,
                    glm::vec2 right_top,
                    glm::vec2 scale ) {
    
    this -> m_Name = name;
    this -> m_ImagePath = imagePath;
    this -> m_OnClick = callback;
    this -> left_bottom = left_bottom;
    this -> right_top = right_top;
    this -> pos = left_bottom + (right_top - left_bottom) / 2.0f; // 設定按鈕的中心位置

    this -> SetDrawable(std::make_shared<Util::Image>(imagePath));
    this -> SetZIndex(15);

}

void Button::Update() {
    auto mouse_pos = Util::Input::GetCursorPosition();	
    bool inside = IsMouseInside(mouse_pos);
    bool mouseDown = Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB);   // 0 代表左鍵，可視情況改變
    bool mouseUp   = Util::Input::IsKeyUp(Util::Keycode::MOUSE_LB);

    if (inside && mouseDown) {
        m_IsPressed = true;
    }

    if (m_IsPressed && mouseUp) {
        m_IsPressed = false;
        if (inside && m_OnClick) {
            Logger::info( "Button clicked: " + m_Name);
            // 呼叫 callback
            m_OnClick();
        }
    }

    // 如果滑鼠已經離開按鈕範圍，或是按住之後又移出去並放開，可以考慮重置 m_IsPressed
    if (!inside && mouseUp) {
        m_IsPressed = false;
    }
}

bool Button::IsMouseInside(glm::vec2 mousePos) const
{
    return (mousePos.x >= left_bottom.x && mousePos.x <= right_top.x &&
            mousePos.y >= left_bottom.y && mousePos.y <= right_top.y);
}