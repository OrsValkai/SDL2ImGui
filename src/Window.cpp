// Copyright(c) 2024 Valkai-Németh Béla-Örs

#include "Window.hpp"
#include <SDL_image.h>

namespace vo {

    bool Window::Init(int width, int height, Uint32 flags, int imgFlags)
    {
        if (0 != SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO)) {
            return false;
        }

        if (imgFlags != IMG_Init(imgFlags)) {
            SDL_Quit();

            return false;
        }

        if (0 != SDL_CreateWindowAndRenderer(width, height, flags, &m_pWindow, &m_pRenderer)) {
            SDL_Quit();
            IMG_Quit();

            m_pWindow = nullptr;

            return false;
        }

        // For finding out DPI compare these 2
        //int w{ 0 };
        //int h{ 0 };
        //SDL_GetWindowSize(m_pWindow, &w, &h);
        //SDL_GetRendererOutputSize(m_pRenderer, &w, &h);

        SDL_RenderSetVSync(m_pRenderer, 1);


        return true;
    }

    SDL_Renderer* Window::GetRenderer()
    {
        return m_pRenderer;
    }

    Window::~Window()
    {
        if (nullptr == m_pWindow)
            return;

        IMG_Quit();
        SDL_DestroyRenderer(m_pRenderer);
        SDL_DestroyWindow(m_pWindow);
        SDL_Quit();
    }

}