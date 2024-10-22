// Copyright(c) 2024 Valkai-Németh Béla-Örs

#include "PlayerControl.hpp"
#include <SDL.h>

PlayerControl::PlayerControl(PlayGround& playGround, unsigned short startTileId)
    : BaseControl(playGround, startTileId), m_keys({SDLK_LEFT, SDLK_RIGHT, SDLK_UP, SDLK_DOWN, SDLK_LCTRL}) {
}

void PlayerControl::Update(float deltaTime, vo::IDrawable* pDrawable) {
    Move(m_velocity, deltaTime);

    BaseControl::Update(deltaTime, pDrawable);
}

void PlayerControl::OnEvent(const SDL_Event* pEvent) {
    switch (pEvent->type) {
        // Look for a keypress
        case SDL_KEYDOWN:
            if (pEvent->key.keysym.sym == m_keys[0]) {
                m_velocity.x = -1;
                m_velocity.y = 0;
            } else if (pEvent->key.keysym.sym == m_keys[1]) {
                m_velocity.x = 1;
                m_velocity.y = 0;
            } else if (pEvent->key.keysym.sym == m_keys[2]) {
                m_velocity.y = -1;
                m_velocity.x = 0;
            } else if (pEvent->key.keysym.sym == m_keys[3]) {
                m_velocity.y = 1;
                m_velocity.x = 0;
            }
                   
            break;

        // We must also use the SDL_KEYUP events to zero the x
        // and y velocity variables. But we must also be      
        // careful not to zero the velocities when we shouldn't
        case SDL_KEYUP:
            if (pEvent->key.keysym.sym == m_keys[0]) {
                if (m_velocity.x < 0)
                    m_velocity.x = 0;
            } else if (pEvent->key.keysym.sym == m_keys[1]) {
                if (m_velocity.x > 0)
                    m_velocity.x = 0;
            } else if (pEvent->key.keysym.sym == m_keys[2]) {
                if (m_velocity.y < 0)
                    m_velocity.y = 0;
            } else if (pEvent->key.keysym.sym == m_keys[3]
                && m_velocity.y > 0) {
                    m_velocity.y = 0;
            }
            break;

        default:
            break;
    }
}
