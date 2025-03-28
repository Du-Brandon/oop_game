#include "hp.hpp"
#include "Util/Image.hpp"


void hp_pic::Start(glm::vec2 tp) {
    Target_pos = tp;
    this->SetDrawable(
        std::make_shared<Util::Image>("../assets/other/hp.png"));
    this->SetZIndex(7);
    pos = Target_pos + glm::vec2(0.0f, 25.0f);
}

void hp_pic::Update(glm::vec2 tp) {
    Target_pos = tp;

    // 更新血量文本的位置

    hp_scale = static_cast<float>(current_hp) / max_hp;

    pos = Target_pos + glm::vec2(0.0f, 25.0f) - glm::vec2(20.0f,0.0f)+(hp_scale * glm::vec2(20.0f, 0.0f));
    scale = glm::vec2(hp_scale, 1.0f);
    
}

void hp_pic::setpos(glm::vec2 position) {
    pos = position;
}

void hp_pic::set_maxhp(int max_hp) {
    this->max_hp = max_hp;
}

void hp_pic::add_maxhp(int max_hp) {
    this->max_hp += max_hp;
}

void hp_pic::setpic(int hp) {
    this->current_hp = hp;
}

int hp_pic::getHP() const {
    return current_hp;
}