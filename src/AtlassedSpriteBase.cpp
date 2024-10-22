// Copyright(c) 2024 Valkai-Németh Béla-Örs

#include "AtlassedSpriteBase.hpp"
#include <SDL_pixels.h>

namespace vo {
	static inline void AtlassedSpriteBase_CreateDummyTexture(SDL_Renderer* pRenderer, SDL_TextureUniquePtr& upTexture) {
		// Create a 1 pixel placeholder pink texture instead that will be streched to the size of the
		// missing sprite texture
		Uint32 pixel = 0xFFFF00FF;
		upTexture = SDL_MakeTexturePtr(pRenderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, 1, 1);
		SDL_UpdateTexture(upTexture.get(), nullptr, &pixel, 4);

		// Assert the error, on release builds this won't fire
		SDL_assert(false && "Failed to create texture!");
	}

	AtlassedSpriteBase::AtlassedSpriteBase(SDL_Renderer* pRenderer, const char* pFilePath, unsigned nrSprites)
		: m_pRenderer(pRenderer), m_nrSprites(nrSprites) {
		try {
			m_upTexture = SDL_MakeTexturePtr(m_pRenderer, pFilePath);
		}

		catch (const std::system_error&) {
			AtlassedSpriteBase_CreateDummyTexture(pRenderer, m_upTexture);
		}
	}

	AtlassedSpriteBase::AtlassedSpriteBase(SDL_Renderer* pRenderer, SDL_Surface& surface, unsigned nrSprites)
		: m_pRenderer(pRenderer), m_nrSprites(nrSprites) {
		try {
			m_upTexture = SDL_MakeTexturePtr(m_pRenderer, &surface);
		}

		catch (const std::system_error&) {
			AtlassedSpriteBase_CreateDummyTexture(pRenderer, m_upTexture);
		}
	}

	bool AtlassedSpriteBase::ReadTextureExtents(int& w, int& h) const {
		return (0 == SDL_QueryTexture(m_upTexture.get(), nullptr, nullptr, &w, &h));
	}

}