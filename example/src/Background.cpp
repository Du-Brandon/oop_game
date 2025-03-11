#include "background.hpp"

void BackgroundImage::SetBackground(std::string Image_path) {
    if (Image_path == "background")
    {
        this->SetDrawable(std::make_shared<Util::Image>("../assets/background/lobby.png"));
        this->SetZIndex(0);
        this->m_Visible = true;
    }
    else {
        this->SetDrawable(std::make_shared<Util::Image>("../assets/background/"+ Image_path + ".jpg"));
        this->SetZIndex(0);
        this->m_Visible = true;
        this->m_Transform.scale = glm::vec2(0.5f, 0.5f);
}
}

bool BackgroundImage::getVisible() const {
    return m_Visible;
}