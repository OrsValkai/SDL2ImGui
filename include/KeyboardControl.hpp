// Copyright(c) 2024 Valkai-Németh Béla-Örs

#ifndef KEYBOARD_CONTROL_H
#define KEYBOARD_CONTROL_H

#include "BaseControl.hpp"
#include <array>

class KeyboardControl : public BaseControl
{
public:
	explicit KeyboardControl(PlayGround& playGround, unsigned short startTileId);
	void Update(float deltaTime, Player* pParent) final;
	bool OnEvent(const SDL_Event*) final;

	void RemapKey(size_t id, SDL_KeyCode newKeyCode);

private:
	struct CommandEntry {
		int keyCode;
		vo::Vector2D<signed short> dir;

		CommandEntry(int _keyCode, signed short x, signed short y) : keyCode(_keyCode), dir(x, y) {};
		friend bool operator==(const CommandEntry& lh, const int& rh) { return lh.keyCode == rh; };
	};

	std::array<int, 5> m_keys;
	std::vector<CommandEntry> m_moveCommands{};
	bool m_actionKeyPressed{false};
	bool m_actionConsumed{false};
};

#endif // KEYBOARD_CONTROL_H

