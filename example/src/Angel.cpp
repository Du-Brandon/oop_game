#include "Angel.hpp"
#include <glm/geometric.hpp>

void Angel::Start() {
    pos = {100, 100};

    scale = {0.2f, 0.2f};
}

void Angel::Start(glm::vec2 coordinate) {
    pos = coordinate;
    scale = {0.5f, 0.5f};
    move_speed = 0.0f;

    m_atk = 0;
    name = "Angel";
}

void Angel::Update() {
    if (m_Visible == false){
        return;
    }
    // 輸出新的位置
    // std::cout << "Enemy position: (" << pos.x << ", " << pos.y << ")" << std::endl;

    // 確保敵人不會超出視窗範圍
    // if ((m_wall->boundary_collision_check_leftright(pos + dir * move_speed) == "right") || m_wall->boundary_collision_check_leftright(pos + dir * move_speed) == "lr") {
    //     dir.x = - dir.x;
    // }
    // else if (m_wall->boundary_collision_check_leftright(pos + dir * move_speed) == "left") {
    //     dir.x = - dir.x;
    // }
    // if ((m_wall->boundary_collision_check_updown(pos + dir * move_speed) == "up") || m_wall->boundary_collision_check_updown(pos + dir * move_speed) == "ud") {
    //     dir.y = - dir.y;
    // }
    // else if (m_wall->boundary_collision_check_updown(pos + dir * move_speed) == "down") {
    //     dir.y = - dir.y;
    // }

    // // 更新敵人的位置
    // pos += dir * move_speed;
    if (glm::distance(pos, Giraffe_pos) <= 50.0f) {
        // 
        // 選禮物
        std::cout << "Angel: " << "present" << std::endl;
        m_Visible = false;
    }
    std::cout << "Angelpos: " << pos.x << pos.y << std::endl;
    std::cout << "Giraffepos: " << Giraffe_pos.x << Giraffe_pos.y << std::endl;
}

bool Angel::getVisible() const {
    if (m_Visible == true){
        return true;
    }
    return false;
}

glm::vec2 Angel::move() {
    return dir;
}

void Angel::shoot() {

}