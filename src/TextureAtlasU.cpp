// Copyright(c) 2024 Valkai-Németh Béla-Örs

#include "TextureAtlasU.hpp"
#include "TextureAtlasBase.inl"

namespace vo {

	TextureAtlasU::TextureAtlasU(SDL_Renderer* pRenderer, const char* pFilePath, unsigned width, unsigned height, unsigned m_texCount)
		: TextureAtlasBase(pRenderer, pFilePath, m_texCount), m_width(static_cast<int>(width)), m_height(static_cast<int>(height)) {

		if (ReadTextureExtents(m_nrRows, m_nrColumns)) {
			m_nrRows = std::max(1, m_nrRows / m_width);
			m_nrColumns = m_nrColumns / m_height;
		}
	}

	TextureAtlasU::TextureAtlasU(SDL_Renderer* pRenderer, SDL_Surface& surface, unsigned m_texCount)
		: TextureAtlasBase(pRenderer, surface, m_texCount), m_width(surface.w), m_height(surface.h) {

		if (ReadTextureExtents(m_nrRows, m_nrColumns)) {
			m_nrRows = std::max(1, m_nrRows / m_width);
			m_nrColumns = m_nrColumns / m_height;
		}
	}

	bool TextureAtlasU::Draw(int posX, int posY, unsigned texId, const double angle, const SDL_RendererFlip flip) {
		if (!IsValidSpriteId(texId))
			return false;

		SDL_Rect dstRect = {
			posX,
			posY,
			m_width,
			m_height
		};

		if (0 == m_nrColumns)
			return DrawInternal(nullptr, &dstRect, angle, flip);

		SDL_Rect srcRect = {
			m_width * (static_cast<int>(texId) % m_nrRows),
			m_height * (static_cast<int>(texId) / m_nrRows),
			m_width,
			m_height
		};

		return DrawInternal(&srcRect, &dstRect, angle, flip);
	}

	bool TextureAtlasU::DrawDoubleHeight(int posX, int posY, unsigned texId, const double angle, const SDL_RendererFlip flip) {
		if (!IsValidSpriteId(texId))
			return false;

		SDL_Rect dstRect = {
			posX,
			posY,
			m_width,
			m_height * 2
		};

		if (0 == m_nrColumns)
			return DrawInternal(nullptr, &dstRect, angle, flip);

		SDL_Rect srcRect = {
			m_width * (static_cast<int>(texId) % m_nrRows),
			m_height * (static_cast<int>(texId) / m_nrRows),
			m_width,
			m_height * 2
		};

		return DrawInternal(&srcRect, &dstRect, angle, flip);
	}

	bool TextureAtlasU::DrawTint(int posX, int posY, unsigned texId, Uint8 r, Uint8 g, Uint8 b, const double angle, const SDL_RendererFlip flip)
	{
		if (!IsValidSpriteId(texId))
			return false;

		SDL_Rect dstRect = {
			posX,
			posY,
			m_width,
			m_height
		};

		if (0 == m_nrColumns)
			return DrawTintInternal(nullptr, &dstRect, r, g, b, angle, flip);

		SDL_Rect srcRect = {
			m_width * (static_cast<int>(texId) % m_nrRows),
			m_height * (static_cast<int>(texId) / m_nrRows),
			m_width,
			m_height
		};

		return DrawTintInternal(&srcRect, &dstRect, r, g, b, angle, flip);
	}

}
