#pragma once

#include <string>

#include "Button.hpp"
#include "log_my.hpp"

#include "Util/GameObject.hpp"
#include "Util/Text.hpp"

class Skill_choose : public Util::GameObject {
public:
    Skill_choose() = default;
    ~Skill_choose() override = default;

    void run();
    bool has_clicked_bool() const { return has_clicked; }

private:
    void Start();
    void trigger_skill1();
    void trigger_skill2();
    void trigger_skill3();
    void end();

    bool is_running = false;
    bool has_clicked = false;

    // 技能狀態
    bool bool_skill_double_arrow = false;
    bool bool_skill_rebound_arrow = false;
    bool bool_skill_smart = false;

    std::shared_ptr<Button> m_Button1 = std::make_shared<Button>();
    std::shared_ptr<Button> m_Button2 = std::make_shared<Button>();
    std::shared_ptr<Button> m_Button3 = std::make_shared<Button>();



};
