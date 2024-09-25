// Copyright(c) 2024 Valkai-Németh Béla-Örs

#include "AtlassedSpriteU.hpp"
#include "AtlassedSpriteBase.inl"

AtlassedSpriteU::AtlassedSpriteU(SDL_Renderer* pRenderer, const char* pFilePath, unsigned width, unsigned height, unsigned nrSprites)
: AtlassedSpriteBase(pRenderer, pFilePath, nrSprites), m_width(static_cast<int>(width)), m_height(static_cast<int>(height)) {

	if (ReadTextureExtents(m_nrRows, m_nrColumns)) {
		m_nrRows = std::max(1, m_nrRows/m_width);
		m_nrColumns = m_nrColumns/m_height;
	}
}

bool AtlassedSpriteU::Draw(float posX, float posY, unsigned spriteId, const double angle, const SDL_RendererFlip flip) {
	if (!IsValidSpriteId(spriteId))
		return false;

	SDL_FRect dstRect = {
		posX,
		posY,
		static_cast<float>(m_width),
		static_cast<float>(m_height)
	};

	if (0 == m_nrColumns)
		return DrawInternal(nullptr, &dstRect, angle, flip);

	SDL_Rect srcRect = {
		m_width * (static_cast<int>(spriteId) % m_nrRows),
		m_height * (static_cast<int>(spriteId) / m_nrRows),
		m_width,
		m_height
	};
	
	return DrawInternal(&srcRect, &dstRect, angle, flip);
}
