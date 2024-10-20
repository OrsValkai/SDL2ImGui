// Copyright(c) 2024 Valkai-Németh Béla-Örs

#ifndef VO_ATLASSED_SPRITE_BASE_INL
#define VO_ATLASSED_SPRITE_BASE_INL

#include "AtlassedSpriteBase.hpp"

namespace vo {

	bool inline AtlassedSpriteBase::IsValidSpriteId(unsigned spriteId) const {
		return spriteId < m_nrSprites;
	}

	bool inline AtlassedSpriteBase::DrawInternal(const SDL_Rect* pSrc, const SDL_Rect* pDest, const double angle, const SDL_RendererFlip flip) {
		return (0 == SDL_RenderCopyEx(m_pRenderer, m_upTexture.get(), pSrc, pDest, angle, nullptr, flip));
	}

}

#endif // VO_ATLASSED_SPRITE_BASE_INL