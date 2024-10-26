// Copyright(c) 2024 Valkai-Németh Béla-Örs

#ifndef AI_CONTROL_H
#define AI_CONTROL_H

#include "BaseControl.hpp"

union SDL_Event;

class AIControl : public BaseControl
{
public:
	explicit AIControl(PlayGround& playGround, unsigned short startTileId);
	void Update(float deltaTime, vo::IDrawable* pDrawable) final;
};

#endif // AI_CONTROL_H

