// Copyright(c) 2024 Valkai-Németh Béla-Örs

#ifndef PLAYER_SPRITE_H
#define PLAYER_SPRITE_H

#include "AtlassedSpriteU.hpp"
#include "SpriteAnimator.hpp"

enum class AnimId : unsigned char
{
	IdleBack = 0,
	IdleRight,
	IdleFront,
	IdleLeft,
	WalkBack,
	WalkRight,
	WalkFront,
	WalkLeft,
	AnimIdsCount
};

class PlayerSprite : public SpriteAnimator<unsigned char> {
private:
	std::shared_ptr<AtlassedSpriteU> m_atlassedSprite;

public:
	PlayerSprite(SDL_Renderer* pRenderer, const char* pFilePath, unsigned width, unsigned height, unsigned nrSprites);
	
	bool DrawAnimated(int posX, int posY, AnimId animId, float deltaTime);
};

#endif // PLAYER_SPRITE_H

