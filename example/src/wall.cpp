

#include "pch.hpp" // IWYU pragma: export
#include <glm/fwd.hpp>

#include "Wall.hpp"

void Wall::Start(float up_boundary, float down_boundary, float left_boundary, float right_boundary , float nextleveldoorup , float nextleveldoordown) {
    // up208 down590 left-458 right262
    this->up_boundary = up_boundary;
    this->down_boundary = down_boundary;
    this->left_boundary = left_boundary;
    this->right_boundary = right_boundary;
    this->nextleveldoorup = nextleveldoorup;
    this->nextleveldoordown = nextleveldoordown;
}

void Wall::setwall(glm::vec2 coordinate_left_bottom,glm::vec2  coordinate_right_top) {
    set_Square_Coordinate(coordinate_left_bottom, coordinate_right_top);
    is_circle = false;
}

void Wall::setwall(glm::vec2 coordinate_center, float radius) {
    set_Circle_Coordinate(coordinate_center, radius);
    is_circle = true;
}

void Wall::clear(){
    square_coordinate.clear();
    square_coordinate_list.clear();
    is_circle = false;
}

void Wall::Update() {
    // 可能用不到
    
}

void Wall::end() {
    // 可能用不到
}

std::string Wall::boundary_collision_check_leftright(glm::vec2 coordinate){
    // std::cout << up_boundary << " " << coordinate.y << std::endl;
    if (this->collision_check(coordinate)) {
        // std::cout << "lscollision" << std::endl;
        return "lr";
    }
    if (coordinate.x <= left_boundary){
        return "left";
    }
    else if (coordinate.x >= right_boundary){
        return "right";
    }
    return "no";
}

std::string Wall::boundary_collision_check_updown(glm::vec2 coordinate){
    if (this->collision_check(coordinate)) {
        // std::cout << "udcollision" << std::endl;
        return "ud";
    }
    
    if (coordinate.y >= up_boundary){
        return "up";
    }
    else if (coordinate.y <= down_boundary){
        return "down";
    }
    return "no";
}

bool Wall::boundary_collision_check_door(glm::vec2 coordinate) {
    if (coordinate.y >= nextleveldoorup || coordinate.y <= nextleveldoordown) {
        return false;
    }
    return true;
}

bool Wall::nextlevel_collision_check(glm::vec2 coordinate) {
    if (coordinate.x - right_boundary >= 62) {
        return true;
    }
    else {
        return false;
    }
}

bool Wall::collision_check(glm::vec2 coordinate) {
    if (is_circle) {
        float distance = glm::distance(coordinate, center);
        if (distance <= radius) {
            return true;
        }
    } else {
        for (const auto& square : square_coordinate_list) {
            if (coordinate.x >= square[0].x && coordinate.x <= square[1].x) {
                if (coordinate.y >= square[0].y && coordinate.y <= square[1].y) {
                    return true;
                }
            }
        }
    }
    return false;
}

void Wall::set_Square_Coordinate(glm::vec2 coordinate_left_bottom, glm::vec2 coordinate_right_top) {
    square_coordinate.clear();
    square_coordinate.push_back(coordinate_left_bottom);
    square_coordinate.push_back(coordinate_right_top);
    square_coordinate_list.push_back(square_coordinate);
}

void Wall::set_Circle_Coordinate(glm::vec2 coordinate_center, float radius) {
    pos = coordinate_center;
    scale = glm::vec2(radius, radius);
    center = coordinate_center;
    this->radius = radius;
}