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

class PlayerSprite : public vo::SpriteAnimator<unsigned char> {
private:
	std::shared_ptr<vo::AtlassedSpriteU> m_atlassedSprite;

public:
	PlayerSprite(SDL_Renderer* pRenderer, const char* pFilePath, unsigned width, unsigned height, unsigned nrSprites);
	PlayerSprite(SDL_Renderer* pRenderer, SDL_Surface& surface, unsigned nrSprites);

	bool Draw(int posX, int posY, AnimId animId, float deltaTime, const double angle=0);
};

#endif // PLAYER_SPRITE_H

