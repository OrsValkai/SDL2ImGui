// Copyright(c) 2024 Valkai-Németh Béla-Örs

#ifndef AI_CONTROL_H
#define AI_CONTROL_H

#include "BaseControl.hpp"

union SDL_Event;

class AIControl : public BaseControl
{
public:
	explicit AIControl(PlayGround& playGround, unsigned short startTileId);
	void Update(float deltaTime, Player* pParent) final;

private:
	unsigned short m_prevId{std::numeric_limits<unsigned short>::max()};
	bool m_shouldPickNewTarget{true};
};

#endif // AI_CONTROL_H

