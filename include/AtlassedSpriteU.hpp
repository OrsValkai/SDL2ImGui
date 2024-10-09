// Copyright(c) 2024 Valkai-Németh Béla-Örs

#ifndef ATLASSED_SPRITE_UNIFORM_H
#define ATLASSED_SPRITE_UNIFORM_H

#include "AtlassedSpriteBase.hpp"

class AtlassedSpriteU : public AtlassedSpriteBase {
private:
	int m_nrRows = 1;
	int m_nrColumns = 0;
	int m_width;
	int m_height;

public:
	AtlassedSpriteU(SDL_Renderer* pRenderer, const char* pFilePath, unsigned width, unsigned height, unsigned nrSprites);
	bool Draw(int posX, int posY, unsigned spriteId, const double angle=0, const SDL_RendererFlip flip=SDL_RendererFlip::SDL_FLIP_NONE) override;
	~AtlassedSpriteU() override = default;
};

#endif // ATLASSED_SPRITE_UNIFORM_H
