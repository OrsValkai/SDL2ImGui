// Copyright(c) 2024 Valkai-Németh Béla-Örs

#ifndef VO_TEXTURE_ATLAS_BASE_H
#define VO_TEXTURE_ATLAS_BASE_H

#include "SDL_Wrapper.hpp"

namespace vo {

	class TextureAtlasBase
	{
	public:
		TextureAtlasBase(SDL_Renderer* pRenderer, const char* pFilePath, unsigned m_texCount);
		TextureAtlasBase(SDL_Renderer* pRenderer, SDL_Surface& surface, unsigned m_texCount);
		TextureAtlasBase(const TextureAtlasBase&) = delete;
		TextureAtlasBase& operator=(const TextureAtlasBase&) = delete;
		virtual bool Draw(int posX, int posY, unsigned texId, const double angle = 0, const SDL_RendererFlip flip = SDL_RendererFlip::SDL_FLIP_NONE) = 0;
		virtual bool DrawTint(int posX, int posY, unsigned texId, Uint8 r, Uint8 g, Uint8 b, const double angle = 0, const SDL_RendererFlip flip = SDL_RendererFlip::SDL_FLIP_NONE) = 0;
		bool IsValidSpriteId(unsigned texId) const;
		virtual ~TextureAtlasBase() = default;

	protected:
		bool ReadTextureExtents(int& w, int& h) const;
		bool DrawInternal(const SDL_Rect* pSrc, const SDL_Rect* pDest, const double angle, const SDL_RendererFlip flip);
		bool DrawTintInternal(const SDL_Rect* pSrc, const SDL_Rect* pDest, Uint8 r, Uint8 g, Uint8 b, const double angle, const SDL_RendererFlip flip);

	private:
		SDL_TextureUniquePtr m_upTexture;
		SDL_Renderer* m_pRenderer;
		unsigned m_texCount;
	};

}

#endif // VO_TEXTURE_ATLAS_BASE_H