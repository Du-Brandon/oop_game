#pragma once

#include <string>

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"

class BackgroundImage : public Util::GameObject {
    
public:
    void SetBackground(std::string Image_path);
    void nextbackground(int now_level);
    void win_background();
    bool getVisible() const;
private:
    int if_level_pass = 0;
    int level = 0;
};
