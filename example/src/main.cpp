#include "App.hpp" 
#include "log_my.hpp"

#include "Core/Context.hpp"

#include "Util/Input.hpp"

int main(int, char **) {
    auto context = Core::Context::GetInstance();
    App app;
    Logger::init("../assets/log/log.txt");
    // set icon in window.
    context->SetWindowIcon(ASSETS_DIR "/icon.jpg"); //設定exe圖式
    Logger::info("Game start");

    while (!context->GetExit()) {
        context->Setup();

        switch (app.GetCurrentState()) {
        case App::State::START:
            app.Start();
            break;

        case App::State::UPDATE:
            app.Update();
            break;
        
        case App::State::BOSSUPDATE:
            app.Boss_Update();
            break;
        case App::State::END:
            
            app.End();
            context->SetExit(true);
            Logger::shutdown();
            break;
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        context->Update();
    }
    return 0;
}
