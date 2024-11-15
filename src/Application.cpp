// Copyright(c) 2024 Valkai-Németh Béla-Örs

#include "Application.hpp"
#include <SDL_image.h>

namespace vo {

    Application::Application(const vo::AppSettings& appSettings, int imgFlags) {
        if (0 != SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO)) {
            return;
        }

        if (imgFlags != IMG_Init(imgFlags)) {
            SDL_Quit();

            return;
        }

        if (0 != SDL_CreateWindowAndRenderer(appSettings.m_wWidth, appSettings.m_wHeight, appSettings.ToWindowFlags(), &m_pWindow, &m_pRenderer)) {
            SDL_Quit();
            IMG_Quit();

            m_pWindow = nullptr;
            m_pRenderer = nullptr;

            return;
        }

        // For finding out DPI compare these 2
        //int w{ 0 };
        //int h{ 0 };
        //SDL_GetWindowSize(m_pWindow, &w, &h);
        //SDL_GetRendererOutputSize(m_pRenderer, &w, &h);

        m_wWidth = static_cast<unsigned short>(appSettings.m_wWidth);
        m_wHeight = static_cast<unsigned short>(appSettings.m_wHeight);

        SDL_RenderSetVSync(m_pRenderer, 1);
    }

    void Application::SetWindowName(const char* pName) {
        SDL_SetWindowTitle(m_pWindow, pName);
    }

    Application::~Application() {
        if (nullptr == m_pWindow)
            return;

        IMG_Quit();
        SDL_DestroyRenderer(m_pRenderer);
        SDL_DestroyWindow(m_pWindow);
        SDL_Quit();
    }

}