// Copyright(c) 2024 Valkai-Németh Béla-Örs

#include <iostream>

#include "Player.hpp"
#include "PlayGround.hpp"
#include "TimerHR.hpp"

class Singleton {
private:
    size_t m_nrCalls{0};

    Singleton() = default;

public:
    void CallMe() {
        m_nrCalls++;

        std::cout << "Glad you called " << m_nrCalls << " times!" << std::endl;
    }

    static Singleton& GetInstance() {
        static Singleton sInstance;

        return sInstance;
    }
};

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

    if (0 != SDL_CreateWindowAndRenderer(1024, 768, /*SDL_WINDOW_FULLSCREEN | SDL_WINDOW_BORDERLESS |*/ SDL_WINDOW_ALLOW_HIGHDPI, &pWindow, &pRenderer)) {
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
        TimerHR timerHR;
       
        //Player player1(pRenderer, "Combined64.png_", 64, 56, 160);
        Player player1(pRenderer, "Combined64.png", 64, 102, 160);
        
        //timerHR.Start();
        Player player2(player1);
        //std::cout << "Make texture took: " << timerHR.MarkUS() << "us\n";

        timerHR.Start(); // start to clear time spent before
        while (true) {
            float deltaTime = timerHR.StartMS(); // read time spent in loop and restart

            SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
            SDL_RenderClear(pRenderer);

            auto& tileEntry1 = pPlayGround->GetTileAt(2, 1);
            tileEntry1.m_flags = 0;
            tileEntry1.pDrawable = &player1;

            auto& tileEntry2 = pPlayGround->GetTileAt(4, 5);
            tileEntry2.m_flags = 0;
            tileEntry2.pDrawable = &player2;
            
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
