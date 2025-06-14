#include "Angel.hpp"
#include "Util/Input.hpp"
#include <glm/geometric.hpp>

void Angel::Start(glm::vec2 coordinate) {
    this->SetDrawable(
        std::make_shared<Util::Image>("../assets/sprites/999.png"));
    this->SetZIndex(10);

    pos = coordinate;
    scale = {0.5f * (260.0/1200.0), 0.5f * (224.0/1200.0)};
    move_speed = 0.0f;

    m_atk = 0;
    exp_supply = 0;
    name = "Angel";
}

void Angel::Update() {
    if (m_Visible == false){
        return;
    }

    if (glm::distance(pos, m_Giraffe->coordinate()) <= 50.0f) {
        // 選禮物
        m_Triggered = true;
        std::cout << "Angel: " << "present" << std::endl;
        m_Visible = false;
    }
    
    if (Util::Input::IsKeyDown(Util::Keycode::R)){
        std::cout << "Angelpos: " << pos.x << pos.y << std::endl;
        std::cout << "Giraffepos: " << Giraffe_pos.x << Giraffe_pos.y << std::endl;
    }

}

bool Angel::getVisible() const {
    if (m_Visible == true){
        return true;
    }
    return false;
}

glm::vec2 Angel::move() {
    return {0.0f, 0.0f};
}

void Angel::shoot() {

}