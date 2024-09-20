// Copyright(c) 2024 Valkai-Németh Béla-Örs

#ifndef ATLASSED_SPRITE_BASE_INL
#define ATLASSED_SPRITE_BASE_INL

#include "AtlassedSpriteBase.hpp"

bool inline AtlassedSpriteBase::IsValidSpriteId(unsigned spriteId) const {
	return spriteId < m_nrSprites;
}

bool inline AtlassedSpriteBase::DrawInternal(const SDL_Rect* pSrc, const SDL_Rect* pDest) {
	return (0 == SDL_RenderCopy(m_pRenderer, m_upTexture.get(), pSrc, pDest));
}

#endif // ATLASSED_SPRITE_BASE_INL