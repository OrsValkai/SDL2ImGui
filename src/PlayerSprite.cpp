// Copyright(c) 2024 Valkai-Németh Béla-Örs

#include "PlayerSprite.hpp"

PlayerSprite::PlayerSprite(SDL_Renderer* pRenderer, const char* pFilePath, unsigned width, unsigned height, unsigned nrSprites)
: AtlassedSpriteU(pRenderer, pFilePath, width, height, nrSprites), SpriteAnimator(20) {
	// Idle frames
	AppendSpriteIds({0, 1, 2, 3, 16, 17, 18, 19, 32, 33, 34, 35, 48, 49, 50, 51, 64, 65, 66, 67});
	AppendSpriteIdsAsOffsetFromPrevious(4);
	AppendSpriteIdsAsOffsetFromPrevious(4);
	AppendSpriteIdsAsOffsetFromPrevious(4);

	// Walk frames
	AppendSpriteIdsAsOffsetFromPrevious(80-12);
	AppendSpriteIdsAsOffsetFromPrevious(4);
	AppendSpriteIdsAsOffsetFromPrevious(4);
	AppendSpriteIdsAsOffsetFromPrevious(4);
}

bool PlayerSprite::DrawAnimated(int posX, int posY, AnimId animId, float deltaTime) {
	return AtlassedSpriteU::Draw(posX, posY, ComputeSpriteId(static_cast<unsigned char>(animId), deltaTime));
}