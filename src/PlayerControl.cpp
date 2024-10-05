// Copyright(c) 2024 Valkai-N�meth B�la-�rs

#include "PlayerControl.hpp"
#include <SDL.h>

PlayerControl::PlayerControl(PlayGround& playGround, unsigned short startTileId) : BaseControl(playGround, startTileId) {
}

void PlayerControl::Update(float deltaTime, IDrawable* pDrawable) {
    Move(m_velocity, deltaTime);

    BaseControl::Update(deltaTime, pDrawable);
}

void PlayerControl::OnEvent(const SDL_Event* pEvent) {
    switch (pEvent->type) {
        // Look for a keypress
        case SDL_KEYDOWN:
            switch (pEvent->key.keysym.sym) {
                case SDLK_LEFT:
                    m_velocity.x = -1;
                    m_velocity.y = 0;
                    break;
                case SDLK_RIGHT:
                    m_velocity.x = 1;
                    m_velocity.y = 0;
                    break;
                case SDLK_UP:
                    m_velocity.y = -1;
                    m_velocity.x = 0;
                    break;
                case SDLK_DOWN:
                    m_velocity.y = 1;
                    m_velocity.x = 0;
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
                    if (m_velocity.x < 0)
                        m_velocity.x = 0;
                    break;
                case SDLK_RIGHT:
                    if (m_velocity.x > 0)
                        m_velocity.x = 0;
                    break;
                case SDLK_UP:
                    if (m_velocity.y < 0)
                        m_velocity.y = 0;
                    break;
                case SDLK_DOWN:
                    if (m_velocity.y > 0)
                        m_velocity.y = 0;
                    break;
                default:
                    break;
            }
            break;

        default:
            break;
    }
}
