// Copyright(c) 2024 Valkai-Németh Béla-Örs

#include <iostream>

#include "Player.hpp"
#include "PlayGround.hpp"
#include "TimerHR.hpp"
#include "PlayerControl.hpp"

#include <vector>
#include <array>
#include <algorithm>



int main(int /*argc*/, char* /*argv*/[]) {
    SDL_Renderer* pRenderer = nullptr;
    SDL_Window* pWindow = nullptr;

    if (0 != SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO)) {
        return EXIT_FAILURE;
    }

    if (int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG; imgFlags != IMG_Init(imgFlags)) {
        SDL_Quit();

        return EXIT_FAILURE;
    }

    if (0 != SDL_CreateWindowAndRenderer(1920, 1080, /*SDL_WINDOW_FULLSCREEN | SDL_WINDOW_BORDERLESS |*/ SDL_WINDOW_ALLOW_HIGHDPI, &pWindow, &pRenderer)) {
        SDL_Quit();
        IMG_Quit();
        
        return EXIT_FAILURE;
    }

    // For finding out DPI compare these 2
    int w{ 0 };
    int h{ 0 };
    SDL_GetWindowSize(pWindow, &w, &h);
    SDL_GetRendererOutputSize(pRenderer, &w, &h);

    SDL_RenderSetVSync(pRenderer, 1);

    {
        auto pPlayGround = std::make_unique<PlayGround>(static_cast<unsigned short>(h), static_cast<unsigned short>(w), pRenderer, "EnvAtlas.png");
        auto pPlayerCtrl = std::make_shared<PlayerControl>(*pPlayGround, pPlayGround->GetTileId(1, 2));
        TimerHR timerHR;
       
        //Player player1(pRenderer, "Combined64.png_", 64, 56, 160);
        Player player1(pRenderer, "Combined64.png", 64, 102, 160);
        
        //timerHR.Start();
        Player player2(player1);
        //std::cout << "Make texture took: " << timerHR.MarkUS() << "us\n";

        player1.AddControl(pPlayerCtrl);
        player2.AddControl(std::make_shared<PlayerControl>(*pPlayGround, pPlayGround->GetTileId(5, 4)));
        
        bool shouldExit = false;
        timerHR.Start(); // start to clear time spent before
        while (false == shouldExit) {
            float deltaTime = timerHR.StartMS(); // read time spent in loop and restart
            SDL_Event event;

            while (SDL_PollEvent(&event)) {
                if (SDL_QUIT == event.type)
                    shouldExit = true;
                else
                    pPlayerCtrl->OnEvent(&event);
            }

            player1.Update(deltaTime);
            player2.Update(deltaTime);

            SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
            SDL_RenderClear(pRenderer);
            
            pPlayGround->Draw(deltaTime);
            
            SDL_RenderPresent(pRenderer);
        }
    }

    IMG_Quit();
    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);
    SDL_Quit();
    return EXIT_SUCCESS;
}
