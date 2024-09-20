// Copyright(c) 2024 Valkai-Németh Béla-Örs

#include "AtlassedSpriteBase.hpp"
#include <SDL_pixels.h>

AtlassedSpriteBase::AtlassedSpriteBase(SDL_Renderer* pRenderer, const char* pFilePath, unsigned nrSprites)
: m_pRenderer(pRenderer), m_nrSprites(nrSprites) {
	try {
		m_upTexture = SDL_MakeTexturePtr(m_pRenderer, pFilePath);
	}

	catch (const std::system_error&) {
		// Create a 1 pixel placeholder pink texture instead that will be streched to the size of the
		// missing sprite texture
		Uint32 pixel = 0xFFFF00FF;
		m_upTexture = SDL_MakeTexturePtr(m_pRenderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, 1, 1);
		SDL_UpdateTexture(m_upTexture.get(), nullptr, &pixel, 4);

		// Assert the error, on release builds this won't fire
		SDL_assert(false && "Failed to create texture!");
	}
}

bool AtlassedSpriteBase::ReadTextureExtents(int& w, int& h) const {
	return (0 == SDL_QueryTexture(m_upTexture.get(), nullptr, nullptr, &w, &h));
}