// Copyright(c) 2024 Valkai-Németh Béla-Örs

#ifndef VO_UNIFORM_TEXTURE_ATLAS_H
#define VO_UNIFORM_TEXTURE_ATLAS_H

#include "TextureAtlasBase.hpp"

namespace vo {

	class TextureAtlasU : public TextureAtlasBase {
	private:
		int m_nrRows = 1;
		int m_nrColumns = 0;
		int m_width;
		int m_height;

	public:
		TextureAtlasU(SDL_Renderer* pRenderer, const char* pFilePath, unsigned width, unsigned height, unsigned m_texCount);
		TextureAtlasU(SDL_Renderer* pRenderer, SDL_Surface& surface, unsigned m_texCount);
		bool Draw(int posX, int posY, unsigned texId, const double angle = 0, const SDL_RendererFlip flip = SDL_RendererFlip::SDL_FLIP_NONE) override;
		~TextureAtlasU() override = default;
	};

}

#endif // VO_UNIFORM_TEXTURE_ATLAS_H
