#pragma once

#include "Enemy.hpp"
#include "Wall.hpp"

class Enemy_2 : public Enemy {
public:
    Enemy_2() = default;
    ~Enemy_2() override = default;

    void Update() override;
    void Start() override;
    void Start(glm::vec2 coordinate) override;

    glm::vec2 move() override;
    void shoot() override;
    
};