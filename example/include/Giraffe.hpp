#ifndef GIRAFFE_HPP
#define GIRAFFE_HPP

#include <utility>
#include "pch.hpp" // IWYU pragma: export
#include "Util/Renderer.hpp"

#include "GiraffeText.hpp"
// #include "Arrow.hpp"
#include "Util/GameObject.hpp"
#include "Util/Text.hpp"

class Giraffe : public Util::GameObject {

public:
    void Update();

    void Start();
    void ShootArrow(); // 添加生成 Arrow 的方法

    glm::vec2 coordinate();

private:    
    glm::vec2 &pos = m_Transform.translation; // 長頸鹿的位置
    glm::vec2 &scale = m_Transform.scale; // 長頸鹿的大小
    float &rotation = m_Transform.rotation; // 長頸鹿的旋轉角度
    std::shared_ptr<GiraffeText> m_GiraffeText;

};

#endif
