

#include "pch.hpp" // IWYU pragma: export
#include <glm/fwd.hpp>

#include "Wall.hpp"

void Wall::Start(glm::vec2 coordinate_left_bottom,glm::vec2  coordinate_right_top) {
    set_Square_Coordinate(coordinate_left_bottom, coordinate_right_top);
    is_circle = false;
}

void Wall::Start(glm::vec2 coordinate_center, float radius) {
    set_Circle_Coordinate(coordinate_center, radius);
    is_circle = true;
}

void Wall::Update() {
    // 可能用不到
}

void Wall::end() {
    // 可能用不到
}

bool Wall::collision_check(glm::vec2 coordinate) {
    if (!is_circle && coordinate.x >= left_bottom.x && coordinate.x <= right_top.x && coordinate.y >= left_bottom.y && coordinate.y <= right_top.y) {
        return true;
    }
    else if (is_circle && glm::distance(coordinate, center) <= radius) {
        return true;
    }
    return false;
}

void Wall::set_Square_Coordinate(glm::vec2 coordinate_left_bottom, glm::vec2 coordinate_right_top) {
    pos = (coordinate_left_bottom + coordinate_right_top) / 2.0f;
    scale = coordinate_right_top - coordinate_left_bottom;
    left_bottom = coordinate_left_bottom;
    right_top = coordinate_right_top;
}

void Wall::set_Circle_Coordinate(glm::vec2 coordinate_center, float radius) {
    pos = coordinate_center;
    scale = glm::vec2(radius, radius);
    center = coordinate_center;
    this->radius = radius;
}