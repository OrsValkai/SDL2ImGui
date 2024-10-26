// Copyright(c) 2024 Valkai-Németh Béla-Örs

#ifndef PLAYER_CONTROL_H
#define PLAYER_CONTROL_H

#include "BaseControl.hpp"
#include <array>

union SDL_Event;

class PlayerControl : public BaseControl
{
public:
	explicit PlayerControl(PlayGround& playGround, unsigned short startTileId);
	void Update(float deltaTime, vo::IDrawable* pDrawable) final;
	void OnEvent(const SDL_Event*);

	void RemapKey(size_t id, SDL_KeyCode newKeyCode);

private:
	vo::Vector2D<signed short> m_velocity{0, 0};
	std::array<int, 5> m_keys{0};
};

#endif // PLAYER_CONTROL_H

