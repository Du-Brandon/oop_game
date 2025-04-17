#pragma once

#include <functional>
#include <string>

#include "pch.hpp" // IWYU pragma: export
#include "Util/GameObject.hpp"
#include "Util/Image.hpp"


class Button : public Util::GameObject{
public:
    using OnClickCallback = std::function<void()>;
    Button () = default;

    ~Button () override = default;
    void Start( const std::string& name, 
                const std::string& imagePath, 
                const OnClickCallback& callback = nullptr,
                glm::vec2 left_bottom = glm::vec2(0.0f, 0.0f),
                glm::vec2 right_top = glm::vec2(0.0f, 0.0f),
                glm::vec2 scale = glm::vec2(1.0f, 1.0f) ) ;
    void Update() ;

private:
    //  

    bool IsMouseInside(glm::vec2 mousePos) const;
    // 內部資料
    // int m_X, m_Y;                 // 按鈕左上角座標
    // float m_Width, m_Height;        // 按鈕大小
    bool m_IsPressed = false;             // 記錄滑鼠是否在按鈕上被按下
    std::string m_Name;          // 按鈕名稱
    OnClickCallback m_OnClick;    // Callback 函式
    std::string m_ImagePath;      // 圖片路逕

    glm::vec2 &pos = m_Transform.translation; // 按鈕的位置 
    glm::vec2 &scale = m_Transform.scale; // 按鈕的大小
    glm::vec2 left_bottom;
    glm::vec2 right_top;
};