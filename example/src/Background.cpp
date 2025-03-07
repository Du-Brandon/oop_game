#include "background.hpp"

void BackgroundImage::SetBackground(std::string Image_path) {
    if (Image_path == "background")
    {
        this->SetDrawable(std::make_shared<Util::Image>("../assets/sprites/background.png"));
        this->SetZIndex(0);
    }
    else {
        this->SetDrawable(std::make_shared<Util::Image>("../assets/sprites/"+ Image_path + ".png"));
        this->SetZIndex(0);

}
}