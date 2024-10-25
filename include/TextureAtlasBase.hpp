// Copyright(c) 2024 Valkai-Németh Béla-Örs

#ifndef VO_TEXTURE_ATLAS_BASE_H
#define VO_TEXTURE_ATLAS_BASE_H

#include "SDL_Wrapper.hpp"

namespace vo {

	class TextureAtlasBase {
	private:
		SDL_TextureUniquePtr m_upTexture;
		SDL_Renderer* m_pRenderer;
		unsigned m_texCount;

	public:
		TextureAtlasBase(SDL_Renderer* pRenderer, const char* pFilePath, unsigned m_texCount);
		TextureAtlasBase(SDL_Renderer* pRenderer, SDL_Surface& surface, unsigned m_texCount);
		TextureAtlasBase(const TextureAtlasBase&) = delete;
		TextureAtlasBase& operator=(const TextureAtlasBase&) = delete;
		virtual bool Draw(int posX, int posY, unsigned texId, const double angle, const SDL_RendererFlip flip) = 0;
		bool IsValidSpriteId(unsigned texId) const;
		virtual ~TextureAtlasBase() = default;

	protected:
		bool ReadTextureExtents(int& w, int& h) const;
		bool DrawInternal(const SDL_Rect* pSrc, const SDL_Rect* pDest, const double angle, const SDL_RendererFlip flip);
	};

}

#endif // VO_TEXTURE_ATLAS_BASE_H