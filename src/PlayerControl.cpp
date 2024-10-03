// Copyright(c) 2024 Valkai-Németh Béla-Örs

#include "PlayerControl.hpp"
#include <SDL.h>

PlayerControl::PlayerControl(PlayGround& playGround, unsigned short startTileId) : BaseControl(playGround, startTileId) {
}

void PlayerControl::OnEvent(const SDL_Event* pEvent) {
    switch (pEvent->type) {
        // Look for a keypress
        case SDL_KEYDOWN:
            // Check the SDLKey values and move change the coords
            switch (pEvent->key.keysym.sym) {
                case SDLK_LEFT:
                    m_xVelocity = -1;
                    break;
                case SDLK_RIGHT:
                    m_xVelocity = 1;
                    break;
                case SDLK_UP:
                    m_yVelocity = -1;
                    break;
                case SDLK_DOWN:
                    m_yVelocity = 1;
                    break;
                default:
                    break;
                }
                break;
            // We must also use the SDL_KEYUP events to zero the x
            // and y velocity variables. But we must also be      
            // careful not to zero the velocities when we shouldn't
        case SDL_KEYUP:
            switch (pEvent->key.keysym.sym) {
                case SDLK_LEFT:
                    if (m_xVelocity < 0)
                        m_xVelocity = 0;
                    break;
                case SDLK_RIGHT:
                    if (m_xVelocity > 0)
                        m_xVelocity = 0;
                    break;
                case SDLK_UP:
                    if (m_yVelocity < 0)
                        m_yVelocity = 0;
                    break;
                case SDLK_DOWN:
                    if (m_yVelocity > 0)
                        m_yVelocity = 0;
                    break;
                default:
                    break;
            }
            break;

        default:
            break;
    }
}
