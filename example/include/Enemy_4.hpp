#include <cmath>
#include <vector>
#include <memory>

#include "Enemy.hpp"
#include "Wall.hpp"
#include "EnemyArrow.hpp"

class Enemy_4 : public Enemy , public std::enable_shared_from_this<Enemy> {
public:
    Enemy_4() = default;
    ~Enemy_4() override = default;

    void Update() override;
    void Start() override;
    void Start(glm::vec2 coordinate) override;

    glm::vec2 move() override;
    void shoot() override;

private:

};