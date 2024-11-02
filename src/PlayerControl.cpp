// Copyright(c) 2024 Valkai-Németh Béla-Örs

#include "PlayerControl.hpp"
#include <SDL.h>

#include <algorithm>

PlayerControl::PlayerControl(PlayGround& playGround, unsigned short startTileId)
    : BaseControl(playGround, startTileId), m_keys({SDLK_LEFT, SDLK_RIGHT, SDLK_UP, SDLK_DOWN, SDLK_LCTRL}) {
    m_commands.reserve(m_keys.size());
}

void PlayerControl::Update(float deltaTime, vo::IDrawable* pDrawable) {
    if (!m_commands.empty()) {
        Move(m_commands.back().dir, deltaTime);
    }
    else {
        vo::Vector2D<signed short> zero{};
        Move(zero, deltaTime);
    }

    BaseControl::Update(deltaTime, pDrawable);
}

void PlayerControl::OnEvent(const SDL_Event* pEvent) {
    switch (pEvent->type) {
            // Look for a keypress
            case SDL_KEYDOWN: {
                if (m_commands.end() != std::find(m_commands.begin(), m_commands.end(), pEvent->key.keysym.sym))
                    break; // already pressed, and not released yet

                if (pEvent->key.keysym.sym == m_keys[0]) {
                    m_commands.emplace_back(m_keys[0], static_cast<signed short>(-1), static_cast<signed short>(0));
                }
                else if (pEvent->key.keysym.sym == m_keys[1]) {
                    m_commands.emplace_back(m_keys[1], static_cast<signed short>(1), static_cast<signed short>(0));
                }
                else if (pEvent->key.keysym.sym == m_keys[2]) {
                    m_commands.emplace_back(m_keys[2], static_cast<signed short>(0), static_cast<signed short>(-1));
                }
                else if (pEvent->key.keysym.sym == m_keys[3]) {
                    m_commands.emplace_back(m_keys[3], static_cast<signed short>(0), static_cast<signed short>(1));
                }

                break;
            }

            // When released we remove it from commands
            case SDL_KEYUP: {
                m_commands.erase(std::remove_if(m_commands.begin(), m_commands.end(), [pEvent](const CommandEntry& e) { return e.keyCode == pEvent->key.keysym.sym; }), m_commands.end());
                break;
            }

        default:
            break;
    }
}

void PlayerControl::RemapKey(size_t id, SDL_KeyCode newKeyCode) {
    m_keys[id] = newKeyCode;
}
