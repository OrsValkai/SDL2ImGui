// Copyright(c) 2024 Valkai-Németh Béla-Örs

#ifndef PLAYER_CONTROL_H
#define PLAYER_CONTROL_H

#include "BaseControl.hpp"

union SDL_Event;

class PlayerControl : public BaseControl
{
public:
	explicit PlayerControl(PlayGround& playGround, unsigned short startTileId);
	void OnEvent(const SDL_Event*);

private:
	int m_xVelocity {0};
	int m_yVelocity {0};
};

#endif // PLAYER_CONTROL_H

