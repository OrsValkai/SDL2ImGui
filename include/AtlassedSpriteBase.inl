#ifndef ATLASSED_SPRITE_BASE_INL
#define ATLASSED_SPRITE_BASE_INL

#include "AtlassedSpriteBase.hpp"

bool inline AtlassedSpriteBase::IsValidSpriteId(unsigned spriteId) const {
	return spriteId < m_nrSprites;
}

bool inline AtlassedSpriteBase::DrawInternal(const SDL_Rect& src, const SDL_Rect& dest) {
	if (!m_upTexture.get())
		return false;

	return (0 == SDL_RenderCopy(m_pRenderer, m_upTexture.get(), &src, &dest));
}

#endif // ATLASSED_SPRITE_BASE_INL