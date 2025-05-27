#include "Enemy_6.hpp"
#include "config.hpp"
#include "Util/Time.hpp"


#include <iostream>
#include <memory>


// 會射射的敵人

void Enemy_6::Start(glm::vec2 coordinate) {
    this->SetDrawable(
    std::make_shared<Util::Image>("../assets/sprites/enemy.png"));
    this->SetZIndex(5);

    pos = coordinate;
    scale = {0.2f, 0.2f};
    move_speed = 4.0f;

    enemy_hp_start();
}

void Enemy_6::Update() {
    if (m_Visible == false){
        return;
    }

    dir = move();
    if (m_wall->boundary_collision_check_leftright(pos + dir * move_speed) == "right") {
        stuck_move();
    }
    else if (m_wall->boundary_collision_check_leftright(pos + dir * move_speed) == "left") {
        // dir.x = 0;
        stuck_move();
    }
    else if (m_wall->boundary_collision_check_leftright(pos + dir * move_speed) == "lr") {
        // dir.x = 0;
        stuck_move();
    }

    if (m_wall->boundary_collision_check_updown(pos + dir * move_speed) == "up") {
        // dir.y = 0;
        stuck_move();
    }
    else if (m_wall->boundary_collision_check_updown(pos + dir * move_speed) == "down") {
        // dir.y = 0;
        stuck_move();
    }
    else if (m_wall->boundary_collision_check_updown(pos + dir * move_speed) == "ud") {
        // dir.y = 0;
        stuck_move();
    }

    pos += dir * move_speed;

    enemy_hp_update();
}

glm::vec2 Enemy_6::move() {
    if (!m_Giraffe) {
        Logger::warn("Giraffe is nullptr, cannot move towards it.");
        return {0.0f, 0.0f};
    }

    // 計算朝向玩家的方向向量
    glm::vec2 toGiraffe = m_Giraffe->coordinate() - pos;

    // 判斷主要移動方向（上下或左右）
    if (std::abs(toGiraffe.x) > std::abs(toGiraffe.y)) {
        // 左右移動
        dir = {toGiraffe.x > 0 ? 1.0f : -1.0f, 0.0f};
    } else {
        // 上下移動
        dir = {0.0f, toGiraffe.y > 0 ? 1.0f : -1.0f};
    }
    return dir;
}

void Enemy_6 ::shoot() {
    return;
}

void Enemy_6::stuck_move() {
    if (!m_Giraffe) {
        Logger::warn("Giraffe is nullptr, cannot determine stuck movement.");
        return;
    }

    // 計算朝向玩家的方向向量
    glm::vec2 toGiraffe = m_Giraffe->coordinate() - pos;

    // 儲存原本的方向
    glm::vec2 original_dir = dir;

    // 判斷主要移動方向（上下或左右）
    if (std::abs(toGiraffe.x) > std::abs(toGiraffe.y)) {
        // 原本是左右移動，改為上下移動
        if (original_dir.x != 0.0f) {
            dir = {0.0f, toGiraffe.y > 0 ? 1.0f : -1.0f};
        }
    } else {
        // 原本是上下移動，改為左右移動
        if (original_dir.y != 0.0f) {
            dir = {toGiraffe.x > 0 ? 1.0f : -1.0f, 0.0f};
        }
    }

    // 如果新的方向仍然無法移動，則嘗試其他方向
    if (m_wall->boundary_collision_check_leftright(pos + dir * move_speed) != "" ||
        m_wall->boundary_collision_check_updown(pos + dir * move_speed) != "") {
        dir = -original_dir; // 嘗試反方向
    }

    Logger::info("Enemy_6 stuck_move: Adjusted direction to (" +
                 std::to_string(dir.x) + ", " + std::to_string(dir.y) + ")");
}