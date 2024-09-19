#ifndef ATLASSED_SPRITE_UNIFORM_H
#define ATLASSED_SPRITE_UNIFORM_H

#include "AtlassedSpriteBase.hpp"

class AtlassedSpriteU : public AtlassedSpriteBase {
private:
	int m_nrRows;
	int m_nrColumns;
	int m_width;
	int m_height;

public:
	AtlassedSpriteU(SDL_Renderer* pRenderer, const char* pFilePath, unsigned width, unsigned height, unsigned nrSprites);
	bool Draw(int posX, int posY, unsigned spriteId) override;
	~AtlassedSpriteU() override = default;
};

#endif // ATLASSED_SPRITE_UNIFORM_H
