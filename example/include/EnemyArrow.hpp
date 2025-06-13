#pragma once

#include <glm/fwd.hpp>
#include <memory>
#include <vector>
#include <cmath>

#include "pch.hpp" // IWYU pragma: export
#include "Util/GameObject.hpp"
#include "Util/image.hpp"
#include "config.hpp"
#include "Giraffe.hpp" 
#include "Enemy.hpp"
#include "Wall.hpp"


class EnemyArrow : public Util::GameObject {
public:
    EnemyArrow() = default;
    ~EnemyArrow() override = default; // 在 .hpp 文件中聲明解構元

    void setTarget(std::shared_ptr<Enemy> enemy); // 設置射箭的敵人
    void setTarget(std::shared_ptr<Giraffe> giraffe); // 設置目標(玩家)
    void setWall(std::shared_ptr<Wall> wall); // 設置射箭的牆壁

    void Start(std::string image_path = "", glm::vec2 direction = glm::vec2(0.0f,0.0f),std::string enemy_arrow_name = "",bool rebound = false); // 設置箭的圖片和方向
    void Update();
    void Update(bool ignorewall);
    void Setspeed(float speed); // 設置箭的速度
    glm::vec2 coordinate();
    bool shouldDelete() const; // 添加這個方法來檢查箭是否應該被刪除

private:
    glm::vec2 &pos = m_Transform.translation; // 箭的位置
    glm::vec2 &scale = m_Transform.scale; // 箭的大小
    float &rotation = m_Transform.rotation; // 箭的旋轉角度
    float shoot_speed = 10.0f; // 箭的移動速度
    std::string m_enemy_arrow_name; // 箭的名稱

    std::shared_ptr<Enemy> m_Enemy_; // 定義敵人的指針
    std::shared_ptr<Giraffe> m_Giraffe_; // 定義主角的指針
    std::shared_ptr<Wall> m_Wall; // 定義敵人的碰撞邊界

    glm::vec2 m_EnemyCoordinate ; // 敵人的位置
    glm::vec2 m_PlayerCoordinate ;// 玩家的位置

    glm::vec2 m_Direction; // 箭的方向

    bool m_ShouldDelete; // 添加這個成員變數來指示箭是否應該被刪除
    bool m_Rebound = false; // 是否反彈
    int m_LifeCycle = 0; // 生命週期
};

