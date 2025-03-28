#include "hp.hpp"
#include "Util/Image.hpp"


void hp_pic::Start(glm::vec2 tp) {
    Target_pos = tp;
    this->SetDrawable(
        std::make_shared<Util::Image>("../assets/other/hp.png"));
    this->SetZIndex(7);
    pos = Target_pos + glm::vec2(0.0f, 25.0f);
}

void hp_pic::Update() {
    // 更新血量文本的位置
    pos = Target_pos + glm::vec2(0.0f, 25.0f);
    
}