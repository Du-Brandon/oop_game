#include <random>
#include "Skill.hpp"

Skill_choose::Skill_choose() {
    skills = {
        {"雙重射擊", [this]() { this->trigger_skill1(); }, "../assets/buttons/double_arrow.png"},
        {"反彈箭矢", [this]() { this->trigger_skill2(); }, "../assets/buttons/rebound_arrow.png"},
        {"聰明", [this]() { this->trigger_skill3(); }, "../assets/buttons/smart.png"},
        {"憤怒", [this]() { this->trigger_skill4(); }, "../assets/buttons/angry.png"},
        {"加速攻擊", [this]() { this->trigger_skill5(); }, "../assets/buttons/atk_speed.png"},
        {"提升最大血量", [this]() { this->trigger_skill6(); }, "../assets/buttons/add_hp.png"},
        {"無敵", [this]() { this->trigger_skill7(); }, "../assets/buttons/invincible.png"},
        {"背向射擊", [this]() { this->trigger_skill8(); }, "../assets/buttons/back_arrow.png"},
        {"燃燒箭矢", [this]() { this->trigger_skill9(); }, "../assets/buttons/burn_arrow.png"},
        {"攻擊力提升", [this]() { this->trigger_skill10(); }, "../assets/buttons/attack_power.png"},
        {"兩側射擊", [this]() { this->trigger_skill11(); }, "../assets/buttons/two_side_arrow.png"},
        {"斜向射擊", [this]() { this->trigger_skill12(); }, "../assets/buttons/diagonal_arrow.png"},
        
    };
    present = {
        {"加速攻擊", [this]() { this->trigger_skill5(); }, "../assets/buttons/atk_speed.png"},
        {"提升最大血量", [this]() { this->trigger_skill6(); }, "../assets/buttons/add_hp.png"},
        {"補血", [this]() { this->trigger_skill0(); }, "../assets/buttons/add_hp.png"},
        // {"無敵", [this]() { this->trigger_skill7(); }, "../assets/buttons/invincible.png"}
    };
}

void Skill_choose::choose_three_skill() {
    if (is_running) {
        
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
        this->Start("three");
        is_running = true;
    }
}

void Skill_choose::choose_two_skill() {
    if (is_running) {
        m_Button1->SetVisible(true);   // 確保按鈕可見
        m_Button2->SetVisible(true);

        m_Button1->Update();
        m_Button2->Update(); 

        if (Util::Input::IsKeyDown(Util::Keycode::R)) {
            Logger::info("R key pressed, restarting skill selection.");
        }
    }
    else {
        this->Start("two");
        is_running = true;
    }
}

void Skill_choose::Start(std::string name) {
    if (name == "three") {
        if (skills.size() < 3) {
            Logger::error("技能列表不足三個，無法啟動技能選擇界面");
            return;
        }
    
        // 隨機打亂技能列表
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(skills.begin(), skills.end(), g);
    
        // 選擇前三個技能
        auto skill1 = skills[0];
        auto skill2 = skills[1];
        auto skill3 = skills[2];
    
        // 動態生成回調函數並綁定到按鈕
        auto skill1_callback = [this, skill1]() {
            std::get<1>(skill1)();  // 執行技能的回調函數
            this->has_clicked = true;
            this->end();
        };
    
        auto skill2_callback = [this, skill2]() {
            std::get<1>(skill2)();
            this->has_clicked = true;
            this->end();
        };
    
        auto skill3_callback = [this, skill3]() {
            std::get<1>(skill3)();
            this->has_clicked = true;
            this->end();
        };
    
        // 設置按鈕
        m_Button1->Start(std::get<0>(skill1), std::get<2>(skill1), skill1_callback,
            glm::vec2(-370.0f, -30.0f), glm::vec2(-310.0f, 30.0f), glm::vec2(1.0f, 1.0f));
    
        m_Button2->Start(std::get<0>(skill2), std::get<2>(skill2), skill2_callback,
            glm::vec2(-100.0f, -30.0f), glm::vec2(-40.0f, 30.0f), glm::vec2(1.0f, 1.0f));
    
        m_Button3->Start(std::get<0>(skill3), std::get<2>(skill3), skill3_callback,
            glm::vec2(180.0f, -30.0f), glm::vec2(240.0f, 30.0f), glm::vec2(1.0f, 1.0f));
        
        m_Button1->SetZIndex(50);
        m_Button2->SetZIndex(50);
        m_Button3->SetZIndex(50);
    
        // 添加按鈕到渲染樹
        this->AddChild(m_Button1);
        this->AddChild(m_Button2);
        this->AddChild(m_Button3);
    
        // 顯示黑色遮罩
        m_Dark_pic->Start();
        this->AddChild(m_Dark_pic);
        m_Dark_pic->Appear();
    
        // 設置按鈕文本
        m_Skill_choose_text1 ->Start(std::get<0>(skill1), glm::vec2(-330.0f, -50.0f));
        m_Skill_choose_text2 ->Start(std::get<0>(skill2), glm::vec2(-60.0f, -50.0f));
        m_Skill_choose_text3 ->Start(std::get<0>(skill3), glm::vec2(220.0f, -50.0f));
    
        this->AddChild(m_Skill_choose_text1);
        this->AddChild(m_Skill_choose_text2);
        this->AddChild(m_Skill_choose_text3);
    
        m_Skill_choose_text1->SetZIndex(50);
        m_Skill_choose_text2->SetZIndex(50);
        m_Skill_choose_text3->SetZIndex(50);
    
        m_Skill_choose_text1->SetVisible(true);
        m_Skill_choose_text2->SetVisible(true);
        m_Skill_choose_text3->SetVisible(true);
    
        has_clicked = false;
    
        Logger::info("技能選擇界面已啟動");
    }
    else if (name == "two") {
        if (present.size() < 2) {
            Logger::error("技能列表不足兩個，無法啟動技能選擇界面");
            return;
        }
    
        // 隨機打亂技能列表
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(present.begin(), present.end(), g);
    
        // 選擇前兩個技能
        auto skill1 = present[0];
        auto skill2 = present[1];
    
        // 動態生成回調函數並綁定到按鈕
        auto skill1_callback = [this, skill1]() {
            std::get<1>(skill1)();  // 執行技能的回調函數
            this->has_clicked = true;
            this->end();
        };
    
        auto skill2_callback = [this, skill2]() {
            std::get<1>(skill2)();
            this->has_clicked = true;
            this->end();
        };
    
        // 設置按鈕
        m_Button1->Start(std::get<0>(skill1), std::get<2>(skill1), skill1_callback,
            glm::vec2(-280.0f, -30.0f), glm::vec2(-220.0f, 30.0f), glm::vec2(1.0f, 1.0f));
    
        m_Button2->Start(std::get<0>(skill2), std::get<2>(skill2), skill2_callback,
            glm::vec2(160.0f, -30.0f), glm::vec2(220.0f, 30.0f), glm::vec2(1.0f, 1.0f));
    
        m_Button1->SetZIndex(50);
        m_Button2->SetZIndex(50);
    
        // 添加按鈕到渲染樹
        this->AddChild(m_Button1);
        this->AddChild(m_Button2);
    
        // 顯示黑色遮罩
        m_Dark_pic->Start();
        this->AddChild(m_Dark_pic);
        m_Dark_pic->Appear();
    
        // 設置按鈕文本
        m_Skill_choose_text1
            ->Start(std::get<0>(skill1), glm::vec2(-240.0f, -50.0f));
        m_Skill_choose_text2
            ->Start(std::get<0>(skill2), glm::vec2(200.0f, -50.0f));
        
        this->AddChild(m_Skill_choose_text1);
        this->AddChild(m_Skill_choose_text2);

        m_Skill_choose_text1->SetZIndex(50);
        m_Skill_choose_text2->SetZIndex(50);

        m_Skill_choose_text1->SetVisible(true);
        m_Skill_choose_text2->SetVisible(true);

        has_clicked = false;
        Logger::info("禮物技能選擇界面已啟動");
    }
}
void Skill_choose::trigger_skill0() {
    // 觸發補血技能
    Logger::info("技能0被選擇：補血");
    if (giraffe) giraffe->addHP(200); // 設置長頸鹿的血量
}

void Skill_choose::trigger_skill1() {
    // 觸發雙重射擊技能
    Logger::info("技能1被選擇：雙重射擊");
    bool_skill_double_arrow = true;
    if (giraffe) giraffe->bool_skill_double_arrow = true;
    if (giraffe) giraffe->setAtk(-(giraffe->getAtk() * 0.1)); // 減少長頸鹿傷害的10%
    if (giraffe) giraffe->addSkill_double_arrow(); // 設置長頸鹿的雙重射擊技能
}
 
void Skill_choose::trigger_skill2() {
    // 觸發反彈箭矢技能
    Logger::info("技能2被選擇：反彈箭矢");
    bool_skill_rebound_arrow = true;
    if (giraffe) giraffe->bool_skill_rebound_arrow = true;
    removeSkill("反彈箭矢");
}

void Skill_choose::trigger_skill3() {
    // 觸發智慧之眼技能
    Logger::info("技能3被選擇：聰明");
    bool_skill_smart = true;
    if (giraffe) giraffe->bool_skill_smart = true;
    removeSkill("聰明");
}

void Skill_choose::trigger_skill4() {

    Logger::info("技能4被選擇：憤怒");
    bool_skill_angry = true;
    if (giraffe) giraffe->bool_skill_angry = true;
    removeSkill("憤怒");
}

void Skill_choose::trigger_skill5() {
    Logger::info("技能5被選擇：加速攻擊");
    skill_atk_speed = skill_atk_speed + 1; // 增加攻擊速度
    if (giraffe) giraffe-> setAtk_speed(giraffe->getAtk_speed()*0.1); // 設置長頸鹿的攻擊速度
}

void Skill_choose::trigger_skill6() {
    Logger::info("技能6被選擇：加血");
    skill_add_hp = skill_add_hp + 1; // 增加血量
    if (giraffe) giraffe-> addMaxHP(120); // 設置長頸鹿的血量
}

void Skill_choose::trigger_skill7() {
    Logger::info("技能7被選擇：無敵");
    bool_skill_invincible = true;
    if (giraffe) giraffe->bool_skill_invincible = true;
    removeSkill("無敵");
}

void Skill_choose::trigger_skill8() {
    Logger::info("技能8被選擇：背向射擊");
    bool_skill_back_arrow = true;
    if (giraffe) giraffe->skill_back_arrow_count = 1; // 設置長頸鹿的背向射擊技能
    removeSkill("背向射擊");
}

void Skill_choose::trigger_skill9() {
    Logger::info("技能9被選擇：燃燒箭矢");
    if(giraffe) giraffe->burnarrow = true; // 設置長頸鹿的燃燒箭矢技能
    removeSkill("燃燒箭矢");
}

void Skill_choose::trigger_skill10() {
    Logger::info("技能10被選擇：攻擊力提升");
    if (giraffe) giraffe->setAtk(20); // 增加長頸鹿的攻擊力
}
void Skill_choose::trigger_skill11() {
    Logger::info("技能11被選擇：兩側射擊");
    if (giraffe) giraffe->right_left_side_arrow = 1; // 設置長頸鹿的兩側射擊技能
    removeSkill("兩側射擊");
}

void Skill_choose::trigger_skill12() {
    Logger::info("技能12被選擇：斜向射擊");
    if (giraffe) giraffe->incline_arrow = 1; // 設置長頸鹿的斜向射擊技能
    removeSkill("斜向射擊");
}

void Skill_choose::end() {
    // 結束技能選擇
    is_running = false;
    // 移除按鈕
    m_Button1->SetVisible(false);
    m_Button2->SetVisible(false);
    m_Button3->SetVisible(false);

    m_Skill_choose_text1->SetVisible(false);
    m_Skill_choose_text2->SetVisible(false);
    m_Skill_choose_text3->SetVisible(false);

    m_Dark_pic->Disappear();

    this->RemoveChild(m_Button1);
    this->RemoveChild(m_Button2);
    this->RemoveChild(m_Button3);
}

void Skill_choose::addSkill(const std::string& name, const std::function<void()>& callback, const std::string& iconPath) {
    skills.emplace_back(name, callback, iconPath);
}

void Skill_choose::removeSkill(const std::string& name) {
    auto it = std::remove_if(skills.begin(), skills.end(),
        [&name](const auto& skill) {
            return std::get<0>(skill) == name;
        });
    if (it != skills.end()) {
        Logger::info("技能已刪除：" + name);
        skills.erase(it, skills.end());
    } else {
        Logger::warn("嘗試刪除不存在的技能：" + name);
    }

    if (skills.size() < 3) {
        Logger::error("技能列表不足三個，可能導致技能選擇界面無法正常運行");
    }
}

Skill_choose_text::Skill_choose_text() {
    m_Text = std::make_shared<Util::Text>(m_Font, m_Size, fmt::format("{}", "name"), Util::Color::FromRGB(0, 0, 0));
}

void Skill_choose_text::Start(std::string name , glm::vec2 pos) {
    m_Text->SetText(fmt::format("{}", name));
    this ->pos = pos;
    SetDrawable(m_Text);
}
