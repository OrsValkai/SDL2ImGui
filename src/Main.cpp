// Copyright(c) 2024 Valkai-N�meth B�la-�rs

#include <iostream>

#include "Application.hpp"
#include "Player.hpp"
#include "PlayGround.hpp"
#include "TimerHR.hpp"
#include "PlayerControl.hpp"

class GameApp : public vo::Application
{
public:

    void MainLoop() const {
        auto pRenderer = GetRenderer();
        auto pPlayGround = std::make_unique<PlayGround>(GetWindowWidth(), GetWindowHeight(), pRenderer, "EnvAtlas.png");
        auto pPlayerCtrl1 = std::make_shared<PlayerControl>(*pPlayGround, pPlayGround->GetTileId(1, 2));
        auto pPlayerCtrl2 = std::make_shared<PlayerControl>(*pPlayGround, pPlayGround->GetTileId(5, 4));
        vo::TimerHR timerHR;

        //Player player1(pRenderer, "Combined64.png_", 64, 56, 160);
        Player player1(pRenderer, "Combined64.png", 64, 102, 160);

        //timerHR.Start();
        Player player2(player1);
        //std::cout << "Make texture took: " << timerHR.MarkUS() << "us\n";

        player1.AddControl(pPlayerCtrl1);
        player2.AddControl(pPlayerCtrl2);

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
                if (SDL_QUIT == event.type)
                    shouldExit = true;
                else {
                    pPlayerCtrl1->OnEvent(&event);
                    pPlayerCtrl2->OnEvent(&event);
                }
            }

            player1.Update(deltaTime);
            player2.Update(deltaTime);

            SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
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
