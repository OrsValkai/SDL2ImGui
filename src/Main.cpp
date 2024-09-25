// Copyright(c) 2024 Valkai-Németh Béla-Örs

#include <iostream>
#include <chrono>

#include "PlayerSprite.hpp"
#include "PlayGround.hpp"

int main(int argc, char* argv[]) {
    SDL_Event event;
    SDL_Renderer* pRenderer = nullptr;
    SDL_Window* pWindow = nullptr;


    if (0 != SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO)) {
        return EXIT_FAILURE;
    }

    int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
    if (imgFlags != IMG_Init(imgFlags)) {
        SDL_Quit();

        return EXIT_FAILURE;
    }

    if (0 != SDL_CreateWindowAndRenderer(1024, 768, /*SDL_WINDOW_BORDERLESS | */SDL_WINDOW_ALLOW_HIGHDPI, &pWindow, &pRenderer)) {
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
        auto pPlayGround = std::make_unique<PlayGround>(h, w, pRenderer, "EnvAtlas.png");
        auto now(std::chrono::steady_clock::now());
        auto last(now);
       
        //PlayerSprite aSprite1(pRenderer, "Combined64.png_", 64, 56, 160);
        PlayerSprite aSprite1(pRenderer, "Combined64.png", 64, 102, 160);
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - last);

        PlayerSprite aSprite2(aSprite1);
        std::cout << "Make texture took: " << duration.count() << "ms\n";

        while (true) {
            last = now;
            now = std::chrono::steady_clock::now();

            float deltaTime = std::chrono::duration<float, std::milli>(std::chrono::steady_clock::now() - last).count();

            SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
            SDL_RenderClear(pRenderer);

            auto& tileEntry1 = pPlayGround->GetTileAt(0);
            aSprite1.Draw(tileEntry1.posX, tileEntry1.posY, AnimId::IdleFront, deltaTime);

            auto& tileEntry2 = pPlayGround->GetTileAt(pPlayGround->GetNrOfTiles()-1);
            aSprite2.Draw(tileEntry2.posX, tileEntry2.posY, AnimId::WalkLeft, deltaTime);
            
            pPlayGround->Draw(deltaTime);
            
            SDL_RenderPresent(pRenderer);

            if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
                break;
        }
    }

    IMG_Quit();
    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);
    SDL_Quit();
    return EXIT_SUCCESS;
}
