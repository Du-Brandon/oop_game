#pragma once

#include "Enemy.hpp"

class Enemy_1 : public Enemy {
public:
    Enemy_1() = default;
    ~Enemy_1() override = default;

    void Update() override;
    void Start() override;
    void Start(glm::vec2 coordinate) override;

    glm::vec2 coordinate() const override;
    void move() override;
    int getHP() const override;
    void setHP(int hp) override;
    void setAtk(int atk) override;
    int getAtk() const override;
    void setExp_supply(int exp) override;
    int getExp_supply() const override;
    bool getVisible() const override;

};
