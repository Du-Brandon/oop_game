#ifndef APP_HPP
#define APP_HPP

#include "background.hpp"
#include "pch.hpp" // IWYU pragma: export

#include "Util/Renderer.hpp"

#include "Cat.hpp"
#include "Giraffe.hpp"
#include "GiraffeText.hpp"
#include "Enemy.hpp"
#include "Arrow.hpp"
#include <vector>

class App {
public:
    enum class State {
        START,
        UPDATE,
        END,
    };

    State GetCurrentState() const { return m_CurrentState; }

    void Start();
    void Update();
    void End(); // NOLINT(readability-convert-member-functions-to-static)

private:
void ValidTask();

private:
    enum class player_level  {
        lobby,
        first_level,
        end
    };

    State m_CurrentState = State::START;
    player_level m_player_level = player_level::lobby;

    std::shared_ptr<BackgroundImage> m_Background = std::make_shared<BackgroundImage>();
    bool m_Background_bool = false;
    std::shared_ptr<Giraffe> m_Giraffe = std::make_shared<Giraffe>();
    //    std::shared_ptr<GiraffeText> m_GiraffeText =
    //    std::make_shared<GiraffeText>();

    std::shared_ptr<Cat> m_Cat = std::make_shared<Cat>();
    std::shared_ptr<Enemy> m_Enemy = std::make_shared<Enemy>();
    std::shared_ptr<Enemy> m_Enemy2 = std::make_shared<Enemy>();
    std::shared_ptr<Arrow> m_Arrow = std::make_shared<Arrow>();
    // std::vector<std::shared_ptr<Arrow>> m_Arrows;

    Util::Renderer m_Root;

    bool showDemoWindow = true;
};

#endif
