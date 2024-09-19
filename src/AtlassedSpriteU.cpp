#include "AtlassedSpriteU.hpp"
#include "AtlassedSpriteBase.inl"

AtlassedSpriteU::AtlassedSpriteU(SDL_Renderer* pRenderer, const char* pFilePath, unsigned width, unsigned height, unsigned nrSprites)
: AtlassedSpriteBase(pRenderer, pFilePath, nrSprites), m_width(static_cast<int>(width)), m_height(static_cast<int>(height)) {

	if (ReadTextureExtents(m_nrRows, m_nrColumns)) {
		m_nrRows /= m_width;
		m_nrColumns /= m_height;
	}
}

bool AtlassedSpriteU::Draw(int posX, int posY, unsigned spriteId) {
	if (!IsValidSpriteId(spriteId))
		return false;

	SDL_Rect srcRect;
	srcRect.x = m_width * (spriteId % m_nrRows);
	srcRect.y = m_height * (spriteId / m_nrRows);
	srcRect.w = m_width;
	srcRect.h = m_height;

	SDL_Rect dstRect;
	dstRect.x = posX;
	dstRect.y = posY;
	dstRect.w = srcRect.w;
	dstRect.h = srcRect.h;

	return DrawInternal(srcRect, dstRect);
}
