#pragma once

#include "Enemy.hpp"
#include "Skill.hpp"

class Angel : public Enemy {
public:
    Angel() = default;
    ~Angel() override = default;

    void Update() override;
    void Start(glm::vec2 coordinate) override;
    bool getVisible() const override;

    bool isAngel() const override { return true; }
    // bool shouldTriggerSkillChoose() const;

    glm::vec2 move() override;
    void shoot() override;

    bool m_Triggered = false; // 是否觸發過技能選擇
};