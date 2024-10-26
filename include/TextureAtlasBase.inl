// Copyright(c) 2024 Valkai-Németh Béla-Örs

#ifndef VO_TEXTURE_ATLAS_BASE_INL
#define VO_TEXTURE_ATLAS_BASE_INL

#include "TextureAtlasBase.hpp"

namespace vo {

	bool inline TextureAtlasBase::IsValidSpriteId(unsigned texId) const {
		return texId < m_texCount;
	}

	bool inline TextureAtlasBase::DrawInternal(const SDL_Rect* pSrc, const SDL_Rect* pDest, const double angle, const SDL_RendererFlip flip) {
		return (0 == SDL_RenderCopyEx(m_pRenderer, m_upTexture.get(), pSrc, pDest, angle, nullptr, flip));
	}

	bool inline TextureAtlasBase::DrawTintInternal(const SDL_Rect* pSrc, const SDL_Rect* pDest, Uint8 r, Uint8 g, Uint8 b, const double angle, const SDL_RendererFlip flip) {
		SDL_SetTextureColorMod(m_upTexture.get(), r, g, b);

		return (0 == SDL_RenderCopyEx(m_pRenderer, m_upTexture.get(), pSrc, pDest, angle, nullptr, flip));
	}

}

#endif // VO_TEXTURE_ATLAS_BASE_INL