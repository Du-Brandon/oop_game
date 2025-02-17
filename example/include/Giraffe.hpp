#ifndef GIRAFFE_HPP
#define GIRAFFE_HPP

#include <utility>
#include <vector>
#include "Arrow.hpp"
#include "Enemy.hpp"
#include "pch.hpp" // IWYU pragma: export
#include "Util/Renderer.hpp"
#include "GiraffeText.hpp"
#include "Util/GameObject.hpp"
#include "Util/Text.hpp"

class Arrow;
class Giraffe : public Util::GameObject {

public:

    void Update();

    void Start();
    void ShootArrow(); // 添加生成 Arrow 的方法

    glm::vec2 coordinate();
    void setEnemy(std::shared_ptr<Enemy> enemy); // 添加這個方法來設置 m_Enemy 的指針
private:    
    glm::vec2 &pos = m_Transform.translation; // 長頸鹿的位置
    glm::vec2 &scale = m_Transform.scale; // 長頸鹿的大小
    float &rotation = m_Transform.rotation; // 長頸鹿的旋轉角度
    std::shared_ptr<GiraffeText> m_GiraffeText;
    std::shared_ptr<Enemy> m_Enemy;
    std::vector<std::shared_ptr<Arrow>> m_Arrows; // 添加這個成員變數來存儲 Arrow 對象

};

#endif // GIRAFFE_HPP
