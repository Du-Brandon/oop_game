#include "background.hpp"

void BackgroundImage::SetBackground(std::string Image_path) {
    if (Image_path == "background")
    {
        this->SetDrawable(std::make_shared<Util::Image>("../assets/background/lobby.png"));
        this->SetZIndex(0);
        this->m_Visible = true;
        level = 1;
    }
    else {
        this->SetDrawable(std::make_shared<Util::Image>("../assets/background/"+ Image_path + ".png"));
        this->SetZIndex(0);
        this->m_Visible = true;
        this->m_Transform.scale = glm::vec2(0.5f, 0.5f);
}
}

void BackgroundImage::nextbackground(int now_level) {
    if (if_level_pass == 0){
        if_level_pass = 1;
        this->SetBackground("test" + std::to_string(level) + std::to_string(if_level_pass));
    }
    else if (if_level_pass == 1 && level == now_level) {
        return;
    }
    else {
        if_level_pass = 0;
        
        level = now_level ;
        this->SetBackground("test" + std::to_string(level) + std::to_string(if_level_pass));
    }
}

void BackgroundImage::win_background() {
    this->SetBackground("win_background");
}

bool BackgroundImage::getVisible() const {
    return m_Visible;
}