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

class Skill_choose_text;
class Skill_choose : public Util::GameObject {
public:
    Skill_choose();
    ~Skill_choose() override = default;

    void run();
    bool has_clicked_bool() const { return has_clicked; }

    // 新增：設定外部 giraffe
    void setGiraffe(std::shared_ptr<Giraffe> g) { giraffe = g; }

    // 新增：動態管理技能
    void addSkill(const std::string& name, const std::function<void()>& callback, const std::string& iconPath);
    void removeSkill(const std::string& name);

private:
    void Start();
    void trigger_skill0(); 
    void trigger_skill1();
    void trigger_skill2();
    void trigger_skill3();
    void trigger_skill4();
    void trigger_skill5();
    void trigger_skill6();
    void trigger_skill7();
    void end();

    std::shared_ptr<Dark_pic> m_Dark_pic = std::make_shared<Dark_pic>();

    bool is_running = false;
    bool has_clicked = false;

    // 技能狀態（只記錄選擇，不再直接控制角色技能）
    bool bool_skill_double_arrow = false;
    bool bool_skill_rebound_arrow = false;
    bool bool_skill_smart = false;
    bool bool_skill_angry = false;
    int skill_atk_speed = 0;
    int skill_add_hp = 0;
    bool bool_skill_invincible = false;
    

    // 外部傳入的 giraffe 指標
    std::shared_ptr<Giraffe> giraffe = nullptr;

    std::shared_ptr<Button> m_Button1 = std::make_shared<Button>();
    std::shared_ptr<Button> m_Button2 = std::make_shared<Button>();
    std::shared_ptr<Button> m_Button3 = std::make_shared<Button>();

    std::shared_ptr<Skill_choose_text> m_Skill_choose_text1 = std::make_shared<Skill_choose_text>();
    std::shared_ptr<Skill_choose_text> m_Skill_choose_text2 = std::make_shared<Skill_choose_text>();
    std::shared_ptr<Skill_choose_text> m_Skill_choose_text3 = std::make_shared<Skill_choose_text>();
    // 新增：技能列表
    std::vector<std::tuple<std::string, std::function<void()>, std::string>> skills;
    std::vector<std::tuple<std::string, std::function<void()>, std::string>> present;

};

class Skill_choose_text : public Util::GameObject {
public:
    Skill_choose_text() ;
    ~Skill_choose_text() override = default;

    void Start(std::string name , glm::vec2 pos);
    void Update();  

private:
    glm::vec2 &pos = m_Transform.translation; // 位置
    glm::vec2 &scale = m_Transform.scale; // 縮放比例

    std::string m_Font = "../assets/fonts/wb.ttf";
    int m_Size = 36;
    std::shared_ptr<Util::Text> m_Text;

};