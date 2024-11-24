// Copyright(c) 2024 Valkai-Németh Béla-Örs

#include <iostream>
#include <SDL_image.h>

#include "GameApp.hpp"

int main(int /*argc*/, char* /*argv*/[]) {
    vo::AppSettings appSettings("App.ini");
    GameApp app(appSettings, IMG_INIT_JPG | IMG_INIT_PNG);

    if (nullptr == app.GetRenderer()) {
        return EXIT_FAILURE;
    }

    app.SetWindowName("SDL Game");
    app.MainLoop();

    return EXIT_SUCCESS;
}
