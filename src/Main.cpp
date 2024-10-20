// Copyright(c) 2024 Valkai-Németh Béla-Örs

#include <iostream>

#include "Window.hpp"
#include "Player.hpp"
#include "PlayGround.hpp"
#include "TimerHR.hpp"
#include "PlayerControl.hpp"

int main(int /*argc*/, char* /*argv*/[]) {
    vo::Window window;
    int w{ 1920 };
    int h{ 1080 };

    if (false == window.Init(w, h, /*SDL_WINDOW_FULLSCREEN | SDL_WINDOW_BORDERLESS |*/ SDL_WINDOW_ALLOW_HIGHDPI, IMG_INIT_JPG | IMG_INIT_PNG)) {
        return EXIT_FAILURE;
    }

    SDL_Renderer* pRenderer = window.GetRenderer();
    
    {
        auto pPlayGround = std::make_unique<PlayGround>(static_cast<unsigned short>(w), static_cast<unsigned short>(h), pRenderer, "EnvAtlas.png");
        auto pPlayerCtrl = std::make_shared<PlayerControl>(*pPlayGround, pPlayGround->GetTileId(1, 2));
        vo::TimerHR timerHR;
       
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

    return EXIT_SUCCESS;
}
