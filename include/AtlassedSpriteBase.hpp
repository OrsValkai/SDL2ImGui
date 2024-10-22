// Copyright(c) 2024 Valkai-Németh Béla-Örs

#ifndef VO_ATLASSED_SPRITE_BASE_H
#define VO_ATLASSED_SPRITE_BASE_H

#include "SDL_Wrapper.hpp"

namespace vo {

	class AtlassedSpriteBase {
	private:
		SDL_TextureUniquePtr m_upTexture;
		SDL_Renderer* m_pRenderer;
		unsigned m_nrSprites;

	public:
		AtlassedSpriteBase(SDL_Renderer* pRenderer, const char* pFilePath, unsigned nrSprites);
		AtlassedSpriteBase(SDL_Renderer* pRenderer, SDL_Surface& surface, unsigned nrSprites);
		AtlassedSpriteBase(const AtlassedSpriteBase&) = delete;
		AtlassedSpriteBase& operator=(const AtlassedSpriteBase&) = delete;
		virtual bool Draw(int posX, int posY, unsigned spriteId, const double angle, const SDL_RendererFlip flip) = 0;
		bool IsValidSpriteId(unsigned spriteId) const;
		virtual ~AtlassedSpriteBase() = default;

	protected:
		bool ReadTextureExtents(int& w, int& h) const;
		bool DrawInternal(const SDL_Rect* pSrc, const SDL_Rect* pDest, const double angle, const SDL_RendererFlip flip);
	};

}

#endif // VO_ATLASSED_SPRITE_BASE_H