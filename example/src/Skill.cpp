#include "Skill.hpp"

void Skill_choose::run() {
    if (is_running) {

        // Logger::info("Skill_choose is running");
        // Logger::info("Dark_pic visible: " );
        // Logger::info("Button1 visible: " );

        
        m_Button1->SetVisible(true);   // 確保按鈕可見
        m_Button2->SetVisible(true);
        m_Button3->SetVisible(true);

        m_Button1->Update();
        m_Button2->Update(); 
        m_Button3->Update();

        if (Util::Input::IsKeyDown(Util::Keycode::R)) {
            Logger::info("R key pressed, restarting skill selection.");
        }
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

    m_Dark_pic->Start();
    this->AddChild(m_Dark_pic);
    m_Dark_pic->Appear(); // 初始時顯示黑色遮罩

    has_clicked = false;

    // 設置三個按鈕的位置和圖片
    m_Button1->Start("雙重射擊", "../assets/buttons/double_arrow.png", skill1_callback,
        glm::vec2(-370.0f,-30.0f), glm::vec2(-310.0f,30.0f), glm::vec2(1.0f,1.0f));

    m_Button2->Start("反彈箭矢", "../assets/buttons/rebound_arrow.png", skill2_callback,
        glm::vec2(-100.0f,-30.0f), glm::vec2(-40.0f,30.0f), glm::vec2(1.0f,1.0f));

    m_Button3->Start("聰明", "../assets/buttons/smart.png", skill3_callback,
        glm::vec2(180.0f,-30.0f), glm::vec2(240.0f,30.0f), glm::vec2(1.0f,1.0f));

    this->AddChild(m_Button1);
    this->AddChild(m_Button2);
    this->AddChild(m_Button3);

    Logger::info("技能選擇界面已啟動");

}

void Skill_choose::trigger_skill1() {
    // 觸發雙重射擊技能
    Logger::info("技能1被選擇：雙重射擊");
    bool_skill_double_arrow = true;
    if (giraffe) giraffe->bool_skill_double_arrow = true;
}

void Skill_choose::trigger_skill2() {
    // 觸發反彈箭矢技能
    Logger::info("技能2被選擇：反彈箭矢");
    bool_skill_rebound_arrow = true;
    if (giraffe) giraffe->bool_skill_rebound_arrow = true;
}

void Skill_choose::trigger_skill3() {
    // 觸發智慧之眼技能
    Logger::info("技能3被選擇：聰明");
    bool_skill_smart = true;
    if (giraffe) giraffe->bool_skill_smart = true;
}

void Skill_choose::trigger_skill4() {
    // 觸發技能4（未實現）
    Logger::info("技能4被選擇：未實現");
    bool_skill_angry = true;
    if (giraffe) giraffe->bool_skill_angry = true;
}



void Skill_choose::end() {
    // 結束技能選擇
    is_running = false;
    // 移除按鈕
    m_Button1->SetVisible(false);
    m_Button2->SetVisible(false);
    m_Button3->SetVisible(false);

    m_Dark_pic->Disappear();
}