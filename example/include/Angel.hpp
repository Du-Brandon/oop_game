#pragma once

#include "Enemy.hpp"

class Angel : public Enemy {
public:
    Angel() = default;
    ~Angel() override = default;

    void Update() override;
    void Start() override;
    void Start(glm::vec2 coordinate) override;
    bool getVisible() const override;


    glm::vec2 move() override;
    void shoot() override;
};