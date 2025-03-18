#ifndef ARROW_HPP
#define ARROW_HPP

#include <memory>
#include <vector>

#include "pch.hpp" // IWYU pragma: export
#include "Util/GameObject.hpp"
#include "Giraffe.hpp" 
#include "Enemy.hpp"
#include "Wall.hpp"

class Giraffe;
class Enemy;
class Arrow : public Util::GameObject {
public:
    // Arrow() = default;
    // ~Arrow() override; // 在 .hpp 文件中聲明解構元
    Arrow(); // 構造元
    void setTarget(Giraffe* giraffe); // 設置射箭的人
    void setTarget(Enemy* enemy); // 設置射箭的目標
    void setTargets(std::vector<std::shared_ptr<Enemy>>& enemies); // 設置射箭的目標

    void Update();
    void Start();
    glm::vec2 coordinate();
    bool shouldDelete() const; // 添加這個方法來檢查箭是否應該被刪除

private:
    // 試著繼承enemy看看
    glm::vec2 &pos = m_Transform.translation; // 箭的位置
    glm::vec2 &scale = m_Transform.scale; // 箭的大小
    float &rotation = m_Transform.rotation; // 箭的旋轉角度

    Giraffe*  m_Giraffe_; // 定義主角的指針
    Enemy* m_Enemy_; // 定義敵人的指針
    std::vector<std::shared_ptr<Enemy>> m_Enemies ; // 定義敵人的指針
    // std::shared_ptr<Enemy> m_Enemy_; // 定義敵人的指針
    



    glm::vec2 m_EnemyCoordinate ; // 敵人的位置
    glm::vec2 m_PlayerCoordinate ;// 玩家的位置

    glm::vec2 arrowPosition; // 箭的位置
    glm::vec2 arrowDirection; // 箭的方向
    glm::vec2 m_Direction; // 箭的方向

    bool m_ShouldDelete; // 添加這個成員變數來指示箭是否應該被刪除
};


#endif // ARROW_HPP