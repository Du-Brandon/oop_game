#pragma once

#include <memory>
#include <string>

#include "Button.hpp"
#include "Giraffe.hpp"
#include "log_my.hpp"

#include "Util/GameObject.hpp"
#include "Util/Text.hpp"
#include "Util/Keycode.hpp"
#include "Util/Input.hpp"


class Skill_choose : public Util::GameObject {
public:
    Skill_choose() = default;
    ~Skill_choose() override = default;

    void run();
    bool has_clicked_bool() const { return has_clicked; }

    // 新增：設定外部 giraffe
    void setGiraffe(std::shared_ptr<Giraffe> g) { giraffe = g; }

private:
    void Start();
    void trigger_skill1();
    void trigger_skill2();
    void trigger_skill3();
    void end();

    std::shared_ptr<Dark_pic> m_Dark_pic = std::make_shared<Dark_pic>();
    

    bool is_running = false;
    bool has_clicked = false;

    // 技能狀態（只記錄選擇，不再直接控制角色技能）
    bool bool_skill_double_arrow = false;
    bool bool_skill_rebound_arrow = false;
    bool bool_skill_smart = false;

    // 外部傳入的 giraffe 指標
    std::shared_ptr<Giraffe> giraffe = nullptr;

    std::shared_ptr<Button> m_Button1 = std::make_shared<Button>();
    std::shared_ptr<Button> m_Button2 = std::make_shared<Button>();
    std::shared_ptr<Button> m_Button3 = std::make_shared<Button>();
};
