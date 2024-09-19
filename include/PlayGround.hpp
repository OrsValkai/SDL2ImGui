// Copyright(c) 2024 Valkai-Németh Béla-Örs

#ifndef PLAY_GROUND_H
#define PLAY_GROUND_H

#include <vector>
#include "TileEntry.hpp"
#include "AtlassedSpriteU.hpp"

class PlayGround
{
	std::vector<TileEntry> m_tiles;
	AtlassedSpriteU m_tileSprite;
	unsigned int m_height = 0;
	unsigned int m_width = 0;

public:
	PlayGround(unsigned int screenHeight, unsigned int screenWidth, SDL_Renderer* pRenderer, const char* pFilePathToTileAtlas);
	void Init();
	void Draw(float deltaTime);
};

#endif // PLAY_GROUND_H

