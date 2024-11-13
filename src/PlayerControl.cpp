// Copyright(c) 2024 Valkai-Németh Béla-Örs

#include "PlayerControl.hpp"
#include <SDL.h>

#include <algorithm>

PlayerControl::PlayerControl(PlayGround& playGround, unsigned short startTileId)
    : BaseControl(playGround, startTileId), m_keys({SDLK_LEFT, SDLK_RIGHT, SDLK_UP, SDLK_DOWN, SDLK_LCTRL}) {
    m_moveCommands.reserve(4);
}

void PlayerControl::Update(float deltaTime, Player* pParent) {
    if (!m_moveCommands.empty()) {
        Move(m_moveCommands.back().dir, deltaTime);
    }
    else {
        vo::Vector2D<signed short> zero{};
        Move(zero, deltaTime);
    }

    if (!m_actionConsumed && m_actionKeyPressed) {
        m_actionConsumed = true;
        PlaceBomb();
    }

    BaseControl::Update(deltaTime, pParent);
}

bool PlayerControl::OnEvent(const SDL_Event* pEvent) {
    switch (pEvent->type) {
            // Look for a keypress
            case SDL_KEYDOWN: {
                if (m_moveCommands.end() != std::find(m_moveCommands.begin(), m_moveCommands.end(), pEvent->key.keysym.sym))
                    return false; // already pressed, and not released yet

                if (pEvent->key.keysym.sym == m_keys[0]) {
                    m_moveCommands.emplace_back(m_keys[0], static_cast<signed short>(-1), static_cast<signed short>(0));
                }
                else if (pEvent->key.keysym.sym == m_keys[1]) {
                    m_moveCommands.emplace_back(m_keys[1], static_cast<signed short>(1), static_cast<signed short>(0));
                }
                else if (pEvent->key.keysym.sym == m_keys[2]) {
                    m_moveCommands.emplace_back(m_keys[2], static_cast<signed short>(0), static_cast<signed short>(-1));
                }
                else if (pEvent->key.keysym.sym == m_keys[3]) {
                    m_moveCommands.emplace_back(m_keys[3], static_cast<signed short>(0), static_cast<signed short>(1));
                }
                else if (pEvent->key.keysym.sym == m_keys[4]) {
                    m_actionKeyPressed = true;
                }

                return false;
            }

            // When released we remove it from commands
            case SDL_KEYUP: {
                if (pEvent->key.keysym.sym == m_keys[4]) {
                    m_actionKeyPressed = false;
                    m_actionConsumed = false;
                    return false;
                }

                m_moveCommands.erase(std::remove_if(m_moveCommands.begin(), m_moveCommands.end(), [pEvent](const CommandEntry& e) { return e.keyCode == pEvent->key.keysym.sym; }), m_moveCommands.end());
                return false;
            }

        default:
            return false;
    }
}

void PlayerControl::RemapKey(size_t id, SDL_KeyCode newKeyCode) {
    m_keys[id] = newKeyCode;
}
