#include "Skill.hpp"

void Skill_choose::run() {
    if (is_running) {
        m_Button1->Update();
        m_Button2->Update(); 
        m_Button3->Update();
    }
    else {
        this->Start();
        is_running = true;
    }
}

void Skill_choose::Start() {
    // 初始化三個按鈕，設置它們的回調函數
    auto skill1_callback = [this]() {
        this->trigger_skill1();
        this->has_clicked = true;
        this->end();
    };

    auto skill2_callback = [this]() {
        this->trigger_skill2();
        this->has_clicked = true;
        this->end();
    };

    auto skill3_callback = [this]() {
        this->trigger_skill3();
        this->has_clicked = true;
        this->end();
    };

    // 設置三個按鈕的位置和圖片
    m_Button1->Start("雙重射擊", "../assets/buttons/double_arrow.png", skill1_callback,
        glm::vec2(-350.0f,-10.0f), glm::vec2(-330.0f,10.0f), glm::vec2(1.0f,1.0f));

    m_Button2->Start("反彈箭矢", "../assets/buttons/rebound_arrow.png", skill2_callback,
        glm::vec2(-80.0f,-10.0f), glm::vec2(-60.0f,10.0f), glm::vec2(1.0f,1.0f));

    m_Button3->Start("智慧之眼", "../assets/buttons/smart_eye.png", skill3_callback,
        glm::vec2(200.0f,-10.0f), glm::vec2(220.0f,10.0f), glm::vec2(1.0f,1.0f));
}

void Skill_choose::trigger_skill1() {
    // 觸發雙重射擊技能
    Logger::info("技能1被選擇：雙重射擊");
    bool_skill_double_arrow = true;
}

void Skill_choose::trigger_skill2() {
    // 觸發反彈箭矢技能
    Logger::info("技能2被選擇：反彈箭矢");
    bool_skill_rebound_arrow = true;
}

void Skill_choose::trigger_skill3() {
    // 觸發智慧之眼技能
    Logger::info("技能3被選擇：智慧之眼");
    bool_skill_smart = true;
}

void Skill_choose::end() {
    // 結束技能選擇
    is_running = false;
    // 移除按鈕
    m_Button1->SetVisible(false);
    m_Button2->SetVisible(false);
    m_Button3->SetVisible(false);
}