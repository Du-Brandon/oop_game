#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <tuple>

#include "pch.hpp" // IWYU pragma: export
#include "Util/GameObject.hpp"

class Wall : public Util::GameObject {
public:
    // Wall(); // 構造元

    void Start(float up_boundary, float down_boundary, float left_boundary, float right_boundary,float nextleveldoorup , float nextleveldoordown); // 添加這個方法來建立邊界的坐標
    void setwall(glm::vec2 coordinate_left_bottom, glm::vec2 coordinate_right_top); 
    void setwall(glm::vec2 coordinate_left_bottom, glm::vec2 coordinate_right_top, std::string name); // 添加這個方法來建立邊界的坐標
    void setwall(glm::vec2 coordinate_center, float radius);
    void clear(); // 清除牆壁的坐標
    void Update();
    void end();


    glm::vec2 coordinate();

    std::string boundary_collision_check_updown(glm::vec2 coordinate,std::string username = ""); // 判斷上下邊界碰撞
    std::string boundary_collision_check_leftright(glm::vec2 coordinate,std::string username = ""); // 判斷左右邊界碰撞
    bool boundary_collision_check_door(glm::vec2 coordinate);
    bool nextlevel_collision_check(glm::vec2 coordinate);
    bool collision_check(glm::vec2 coordinate,std::string username = ""); // 判斷是否碰撞

    float getLeftBoundary() const { return left_boundary; } // 獲取左邊界
    float getRightBoundary() const { return right_boundary; } // 獲取右邊界
    float getTopBoundary() const { return up_boundary; } // 獲取上邊界
    float getBottomBoundary() const { return down_boundary; } // 獲取下邊界

private:
    void set_Square_Coordinate(glm::vec2 coordinate_left_bottom, glm::vec2 coordinate_right_top);
    void set_Circle_Coordinate(glm::vec2 coordinate_center, float radius);
    bool is_circle = false; // 判斷牆是不是圓形

    glm::vec2 &pos = m_Transform.translation; // 牆的位置
    glm::vec2 &scale = m_Transform.scale; // 牆的大小
    float &rotation = m_Transform.rotation; // 牆的旋轉角度

    float up_boundary;
    float down_boundary;  
    float left_boundary;
    float right_boundary;
    float nextleveldoorup;
    float nextleveldoordown;
    glm::vec2 left_bottom;
    glm::vec2 right_top;

    // std::vector<glm::vec2> square_coordinate; // 矩形的四個坐標
    std::tuple<glm::vec2,glm::vec2,std::string> square_coordinate_tuple = {glm::vec2(0,0),glm::vec2(0,0),""}; // 矩形的四個坐標
    std::vector<std::tuple<glm::vec2,glm::vec2,std::string>> square_coordinate_list; // 矩形的四個坐標
    glm::vec2 center;
    float radius;
};