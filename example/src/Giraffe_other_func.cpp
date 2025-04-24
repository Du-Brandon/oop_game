#include "Giraffe.hpp"
#include "log_my.hpp"

#include <cmath>
#include <iostream>
#include <chrono>
#include <vector>

#include "Util/Image.hpp"
#include "Util/Time.hpp"
#include "Util/Transform.hpp"
#include "Util/Input.hpp"

#include "config.hpp"

void Dark_pic::Appear() {
    if (!this->m_Visible) {
            this->SetDrawable(
                std::make_shared<Util::Image>("../assets/other/low.png"));
            this->SetZIndex(100);
            scale = glm::vec2(1024.0f / 1920.0f, 800.0f / 1080.0f);
            this->m_Visible = true;
    }
}

void Dark_pic::Disappear() {
    if (this->m_Visible) {
        this->m_Visible = false;
    }
}
 

void Giraffe::DrawDarkOverlay(){

}


// void Giraffe::DrawDarkOverlay() {
//     std::shared_ptr<Core::Drawable> m_Drawable = nullptr;

//     static std::shared_ptr<Util::Image> overlay = std::make_shared<Util::Image>("../assets/other/low.png");

//     // 設定 model 矩陣，將圖片縮放到 1024x800
//     Core::Matrices matrices;
//     matrices.m_Model = glm::mat4(1.0f);
//     // 以中心為原點，先平移到畫面中心，再縮放
//     matrices.m_Model = glm::translate(matrices.m_Model, glm::vec3(1024.0f / 2, 800.0f / 2, 0.0f));
//     matrices.m_Model = glm::scale(matrices.m_Model, glm::vec3(1024.0f, 800.0f, 1.0f));

//     // 設定正交投影，左上(0,0)，右下(1024,800)
//     matrices.m_Projection = glm::ortho(0.0f, 1024.0f, 800.0f, 0.0f, -1.0f, 1.0f);

//     overlay->Draw(matrices);
// }