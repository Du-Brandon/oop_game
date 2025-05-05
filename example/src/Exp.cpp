#include "Exp.hpp"
#include "Giraffe.hpp"
#include "Util/Image.hpp"
#include "log_my.hpp"
#include <glm/fwd.hpp>

void exp_pic::Start(){
    Logger::info("exp_pic Start");

    scale = {0.0f,1.0f};
    this->SetDrawable(
        std::make_shared<Util::Image>("../assets/other/exp.png"));
    this->SetZIndex(7);
    pos = glm::vec2(-200.0f, 250.0f);
    max_exp_list.clear();

    m_Background = std::make_shared<exp_pic_background>();
    m_Background->Start();
    m_Background->setpos(glm::vec2(0.0f, 250.0f));
    this->AddChild(m_Background);

    m_Dark_pic->Appear();
    this->AddChild(m_Dark_pic);
    m_Dark_pic->Disappear();

    m_LevelText = std::make_shared<exp_pic_text>();
    m_LevelText->Start();
    this->AddChild(m_LevelText);
}

void exp_pic::Update(){
    // Logger::info("exp_pic Update");
    exp_scale = static_cast<float>(exp) / max_exp_list[max_exp_iterator];
    pos = glm::vec2(-200.0f, 250.0f) + (exp_scale * glm::vec2(200.0f, 0.0f));
    scale = glm::vec2(exp_scale, 1.0f);

    m_LevelText->Update();
}

void exp_pic::setpos(glm::vec2 position){
    pos = position;
}

void exp_pic::set_maxexp(int max_exp){
    this->max_exp_list.push_back(max_exp);
}

void exp_pic::set_maxexp(std::vector<int> max_exp_list){
    this->max_exp_list = max_exp_list;
}

void exp_pic::add_exp(int exp){
    this->exp += exp;
    if (this->exp >= this->max_exp_list[max_exp_iterator]) {
        if (this->max_exp_iterator == this->max_exp_list.size() - 1){
            Logger::warn("exp_pic: max_exp_iterator out of range");
            this->exp = this->max_exp_list[max_exp_iterator];
        }
        this->exp = this->exp - this->max_exp_list[max_exp_iterator];
        this->max_exp_iterator++;
        m_LevelText->addlevel(1);
    }
    this->Update();
}

void exp_pic::setpic(int exp){
    this->exp = exp;
}

int exp_pic::getEXP() const{
    return exp;
}

int exp_pic::getLevel() const{
    return max_exp_iterator;
}

void exp_pic_background::Start(){
    this->SetDrawable(
        std::make_shared<Util::Image>("../assets/other/exp_.png"));
    this->SetZIndex(6);
    scale = {1.0f,1.0f};
    // this->setpos(glm::vec2(0.0f,230.0f));
}

void exp_pic_background::setpos(glm::vec2 position){
    pos = position;
}

void exp_pic_text::Start(){
    m_Font = "../assets/fonts/Inter.ttf";
    m_Size = 36;
    m_LevelText = std::make_unique<Util::Text>(m_Font, m_Size, fmt::format("Level: {}", level),
        Util::Color::FromRGB(255, 255, 255));

    
    pos = glm::vec2(0.0f, 300.0f);

    SetDrawable(m_LevelText);
}

void exp_pic_text::Update(){
    m_LevelText->SetText(fmt::format("Level: {}", level));

}

void exp_pic_text::addlevel(int level){
    this->level += level;
}