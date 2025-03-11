#pragma once

#include <string>

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"

class BackgroundImage : public Util::GameObject {
    
public:
    void SetBackground(std::string Image_path);
    bool getVisible() const;

};
