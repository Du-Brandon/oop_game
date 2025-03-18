#pragma once

#include "Enemy.hpp"
#include "Wall.hpp"

class Enemy_1 : public Enemy {
public:
    Enemy_1() = default;
    ~Enemy_1() override = default;

    void Update() override;
    void Start() override;
    void Start(glm::vec2 coordinate) override;

    glm::vec2 move() override;
    void shoot() override;

};
