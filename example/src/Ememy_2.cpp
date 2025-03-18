# include "Enemy_2.hpp"

void Enemy_2::Start() {
    pos = {100, 100};

    scale = {0.2f, 0.2f};

}

void Enemy_2::Start(glm::vec2 coordinate) {
    pos = coordinate;
    scale = {0.2f, 0.2f};
}

void Enemy_2::Update(){
    dir = move();
    
    if (m_Visible == false){
        return;
    }
}