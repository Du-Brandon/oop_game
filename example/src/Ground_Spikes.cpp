#include <cmath>

#include "Ground_Spikes.hpp"
#include "log_my.hpp"

#include "Util/Image.hpp"

void Ground_Spikes::Start(glm::vec2 pos) {
    this->SetDrawable(
        std::make_shared<Util::Image>("../assets/sprites/spikes.png"));
    this->SetZIndex(5);

    this -> pos = pos;
}

void Vecter_Ground_Spikes::Start() {
    this -> clear();
}

void Vecter_Ground_Spikes::Add_Spikes(glm::vec2 pos) {
    auto m_Ground_Spike = std::make_shared<Ground_Spikes>();
    m_Ground_Spike->Start(pos);
    m_Ground_Spikes.push_back(m_Ground_Spike);
    this -> AddChild(m_Ground_Spike);
}

bool Vecter_Ground_Spikes::collision_check(glm::vec2 coordinate) {
    for (auto &spike : m_Ground_Spikes) {
        if (std::abs(spike->coordinate().x - coordinate.x) <= 22 && std::abs(spike->coordinate().y - coordinate.y) <= 27) {
            return true;
        }
    }
    return false;
}

void Vecter_Ground_Spikes::clear() {
    if (m_Ground_Spikes.size() > 0){
        for (auto &spike : m_Ground_Spikes) {
            this->RemoveChild(spike);
        }
    }
    m_Ground_Spikes.clear();
}
