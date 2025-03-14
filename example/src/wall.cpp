

#include "pch.hpp" // IWYU pragma: export
#include <glm/fwd.hpp>

#include "Wall.hpp"

void Wall::Start(float up_boundary, float down_boundary, float left_boundary, float right_boundary) {
    // up208 down590 left-458 right262
    this->up_boundary = up_boundary;
    this->down_boundary = down_boundary;
    this->left_boundary = left_boundary;
    this->right_boundary = right_boundary;
}

void Wall::setwall(glm::vec2 coordinate_left_bottom,glm::vec2  coordinate_right_top) {
    set_Square_Coordinate(coordinate_left_bottom, coordinate_right_top);
    is_circle = false;
}

void Wall::setwall(glm::vec2 coordinate_center, float radius) {
    set_Circle_Coordinate(coordinate_center, radius);
    is_circle = true;
}

void Wall::Update() {
    // 可能用不到
    
}

void Wall::end() {
    // 可能用不到
}

std::string Wall::boundary_collision_check_leftright(glm::vec2 coordinate){
    // std::cout << up_boundary << " " << coordinate.y << std::endl;
    if (coordinate.x <= left_boundary){
        return "left";
    }
    else if (coordinate.x >= right_boundary){
        return "right";
    }
    return "no";
}

std::string Wall::boundary_collision_check_updown(glm::vec2 coordinate){
    if (coordinate.y >= up_boundary){
        return "up";
    }
    else if (coordinate.y <= down_boundary){
        return "down";
    }
    return "no";
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