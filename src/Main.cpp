// Copyright(c) 2024 Valkai-Németh Béla-Örs

#include <iostream>

#include "Application.hpp"
#include "Player.hpp"
#include "PlayGround.hpp"
#include "TimerHR.hpp"
#include "PlayerControl.hpp"
#include "AIControl.hpp"

#include <algorithm>

class GameApp : public vo::Application
{
public:
    void MainLoop() const {
        auto pRenderer = GetRenderer();
        auto pPlayGround = std::make_unique<PlayGround>(GetWindowWidth(), GetWindowHeight(), std::make_shared<vo::TextureAtlasU>(pRenderer, "Atlas64.png", 64, 64, 64));
        auto upBG = vo::SDL_MakeTexturePtr(pRenderer, "BG.jpg");
        const auto& posOffset = pPlayGround->GetPosOffset();
        SDL_Rect bgDst{ 0, 0, GetWindowWidth(), GetWindowHeight() };
        SDL_Rect bgSrc{posOffset.x, posOffset.y+8, bgDst.w, bgDst.h};
        vo::TimerHR timerHR;
        std::vector<Player> players;

        players.reserve(4);
        timerHR.Start();
        players.emplace_back(std::make_shared<vo::TextureAtlasU>(pRenderer, "Player64.png", 64, 102, 160), *pPlayGround);
        std::cout << "Make texture took: " << timerHR.MarkUS() << "us\n";
        
        players.push_back(players.back());
        players.push_back(players.back());

        players.at(0).SetControl(std::make_shared<PlayerControl>(*pPlayGround, static_cast<unsigned short>(0)));
        players.at(1).SetControl(std::make_shared<PlayerControl>(*pPlayGround, pPlayGround->GetNrOfTiles() - 1));
        players.at(2).SetControl(std::make_shared<AIControl>(*pPlayGround, pPlayGround->GetTileId(pPlayGround->GetWidth() - 1, 0)));

        players[1].SetTintColor(245, 210, 160);
        players[2].SetTintColor(255, 180, 180);

        if (auto pCtrl = dynamic_cast<PlayerControl*>(players[1].GetCtrl());  nullptr != pCtrl) {
            pCtrl->RemapKey(0, SDLK_a);
            pCtrl->RemapKey(1, SDLK_d);
            pCtrl->RemapKey(2, SDLK_w);
            pCtrl->RemapKey(3, SDLK_s);
            pCtrl->RemapKey(4, SDLK_TAB);
        }

        bool shouldExit = false;
        timerHR.Start(); // start to clear time spent before
        timerHR.Mark();
        while (false == shouldExit) {
            SDL_Event event;

            while (SDL_PollEvent(&event)) {
                if (SDL_QUIT == event.type) {
                    shouldExit = true;
                } else {
                    for (auto& player : players)
                        player.GetCtrl()->OnEvent(&event);
                }
            }

            float deltaTime = timerHR.MS(); // read time spent in loop and restart
            timerHR.Start();

            int nrPlayersAlive = 0;
            for (auto& player : players) {
                player.Update(deltaTime);

                if (player.IsAlive())
                    nrPlayersAlive++;
            }

            if (nrPlayersAlive <= 1) {
                pPlayGround->Reset();

                for (auto& player : players)
                    player.Reset();

                continue;
            }

            SDL_RenderCopy(pRenderer, upBG.get(), &bgSrc, &bgDst);

            pPlayGround->Draw(deltaTime);

            SDL_RenderPresent(pRenderer);
            timerHR.Mark();
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
