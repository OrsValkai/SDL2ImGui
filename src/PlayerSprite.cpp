// Copyright(c) 2024 Valkai-Németh Béla-Örs

#include "PlayerSprite.hpp"

PlayerSprite::PlayerSprite(SDL_Renderer* pRenderer, const char* pFilePath, unsigned width, unsigned height, unsigned nrSprites)
: SpriteAnimator(20) {
	m_atlassedSprite = std::make_shared<vo::AtlassedSpriteU>(pRenderer, pFilePath, width, height, nrSprites);

	SetSpriteIdPattern({ 0, 1, 2, 3, 16, 17, 18, 19, 32, 33, 34, 35, 48, 49, 50, 51, 64, 65, 66, 67 });

	// Idle anims
	AddAnimOffset(0);
	AddAnimOffset(4);
	AddAnimOffset(8);
	AddAnimOffset(12);

	// Walk anims
	AddAnimOffset(80);
	AddAnimOffset(84);
	AddAnimOffset(88);
	AddAnimOffset(92);
}

bool PlayerSprite::Draw(int posX, int posY, AnimId animId, float deltaTime, const double angle) {

	return m_atlassedSprite->Draw(posX, posY, ComputeSpriteId(static_cast<unsigned char>(animId), deltaTime), angle, SDL_FLIP_NONE);
}