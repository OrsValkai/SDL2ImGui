// Copyright(c) 2024 Valkai-Németh Béla-Örs

#ifndef PLAYER_CONTROL_H
#define PLAYER_CONTROL_H

#include "BaseControl.hpp"
#include <array>

class PlayerControl : public BaseControl
{
public:
	explicit PlayerControl(PlayGround& playGround, unsigned short startTileId);
	void Update(float deltaTime, vo::IDrawable* pDrawable) final;
	void OnEvent(const SDL_Event*);

	void RemapKey(size_t id, SDL_KeyCode newKeyCode);

private:
	struct CommandEntry {
		int keyCode;
		vo::Vector2D<signed short> dir;

		CommandEntry(int _keyCode, signed short x, signed short y) : keyCode(_keyCode), dir(x, y) {};
		friend bool operator==(const CommandEntry& lh, const int& rh) { return lh.keyCode == rh; };
	};

	std::array<int, 5> m_keys;
	std::vector<CommandEntry> m_commands{};
};

#endif // PLAYER_CONTROL_H

