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

    glm::vec2 coordinate() const override;
    void move() override;
    void shoot() override;
    int getHP() const override;
    void setHP(int hp) override;
    void setAtk(int atk) override;
    int getAtk() const override;
    void setExp_supply(int exp) override;
    int getExp_supply() const override;
    bool getVisible() const override;

};