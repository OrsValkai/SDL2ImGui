// Copyright(c) 2024 Valkai-Németh Béla-Örs

#include <iostream>

#include "Application.hpp"
#include "Player.hpp"
#include "PlayGround.hpp"
#include "TimerHR.hpp"
#include "PlayerControl.hpp"
#include "AIControl.hpp"

class GameApp : public vo::Application
{
public:
    void MainLoop() const {
        auto pRenderer = GetRenderer();
        auto pPlayGround = std::make_unique<PlayGround>(GetWindowWidth(), GetWindowHeight(), pRenderer, "Atlas64.png");
        auto pPlayerCtrl1 = std::make_shared<PlayerControl>(*pPlayGround, pPlayGround->GetTileId(1, 2));
        auto pPlayerCtrl2 = std::make_shared<PlayerControl>(*pPlayGround, pPlayGround->GetTileId(5, 4));
        vo::TimerHR timerHR;

        timerHR.Start();
        Player player1(std::make_shared<vo::TextureAtlasU>(pRenderer, "Player64.png", 64, 102, 160));
        std::cout << "Make texture took: " << timerHR.MarkUS() << "us\n";
        
        Player player2(player1);
        Player player3(player1);

        player1.SetControl(pPlayerCtrl1);
        player2.SetControl(pPlayerCtrl2);
        player3.SetControl(std::make_shared<AIControl>(*pPlayGround, pPlayGround->GetTileId(3, 4)));

        player2.SetTintColor(245, 210, 160);
        player3.SetTintColor(255, 180, 180);

        pPlayerCtrl2->RemapKey(0, SDLK_a);
        pPlayerCtrl2->RemapKey(1, SDLK_d);
        pPlayerCtrl2->RemapKey(2, SDLK_w);
        pPlayerCtrl2->RemapKey(3, SDLK_s);
        pPlayerCtrl2->RemapKey(4, SDLK_TAB);

        bool shouldExit = false;
        timerHR.Start(); // start to clear time spent before
        while (false == shouldExit) {
            float deltaTime = timerHR.StartMS(); // read time spent in loop and restart
            SDL_Event event;

            while (SDL_PollEvent(&event)) {
                if (SDL_QUIT == event.type) {
                    shouldExit = true;
                } else {
                    pPlayerCtrl1->OnEvent(&event);
                    pPlayerCtrl2->OnEvent(&event);
                }
            }

            player1.Update(deltaTime);
            player2.Update(deltaTime);
            player3.Update(deltaTime);

            SDL_SetRenderDrawColor(pRenderer, 30, 30, 30, SDL_ALPHA_OPAQUE);
            SDL_RenderClear(pRenderer);

            pPlayGround->Draw(deltaTime);

            SDL_RenderPresent(pRenderer);
        }
    }
};

int main(int /*argc*/, char* /*argv*/[]) {
    vo::AppSettings appSettings("App.ini");
    GameApp app;

    if (false == app.Init(appSettings, IMG_INIT_JPG | IMG_INIT_PNG)) {
        return EXIT_FAILURE;
    }

    app.SetWindowName("SDL Game");
    app.MainLoop();

    return EXIT_SUCCESS;
}
