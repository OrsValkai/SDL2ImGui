// Copyright(c) 2024 Valkai-Németh Béla-Örs

#include <iostream>

#include "Application.hpp"
#include "Player.hpp"
#include "PlayGround.hpp"
#include "TimerHR.hpp"
#include "PlayerControl.hpp"

#include <fstream>
#include <string>

class GameApp : public vo::Application
{
public:

    void MainLoop() const {
        auto pRenderer = GetRenderer();
        auto pPlayGround = std::make_unique<PlayGround>(GetWindowWidth(), GetWindowHeight(), pRenderer, "EnvAtlas.png");
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
};

class AppSettings {
public:
    int wWidth = 0;
    int wHeight = 0;
    bool isFullScreen = false;
    bool isBorderless = false;

    explicit AppSettings(const char* iniFilePath) {
        std::ifstream file(iniFilePath);

        if (file.is_open()) {
            std::string readStr = "Dummy string to preallocate";

            while (!file.eof()) {
                std::getline(file, readStr);

                if ('[' == readStr[0])
                    continue;

                if (std::string::npos != readStr.find("width")) {
                    wWidth = GetValue(readStr);
                } else if (std::string::npos != readStr.find("height")) {
                    wHeight = GetValue(readStr);
                } else if (std::string::npos != readStr.find("fullscreen")) {
                    isFullScreen = 0 != GetValue(readStr);
                } else if (std::string::npos != readStr.find("borderless")) {
                    isBorderless = 0 != GetValue(readStr);
                }
            }
        }
    }

    Uint32 ToWindowFlags() const {
        Uint32 flags = SDL_WINDOW_ALLOW_HIGHDPI;

        if (isFullScreen)
            flags |= SDL_WINDOW_FULLSCREEN;

        if (isBorderless)
            flags |= SDL_WINDOW_BORDERLESS;

        return flags;
    }

private:
    int GetValue(const std::string& str) const {
        for (size_t i = str.size() - 1; i > 0; --i) {
            if (!isdigit(str[i])) {
                return atoi(str.substr(i+1, str.size()-i).c_str());
            }
        }

        return 0;
    }
};

int main(int /*argc*/, char* /*argv*/[]) {
    AppSettings appSettings("App.ini");
    GameApp app;

    if (false == app.Init(appSettings.wWidth, appSettings.wHeight, appSettings.ToWindowFlags(), IMG_INIT_JPG | IMG_INIT_PNG)) {
        return EXIT_FAILURE;
    }

    app.SetWindowName("SDL Game");
    app.MainLoop();

    return EXIT_SUCCESS;
}
