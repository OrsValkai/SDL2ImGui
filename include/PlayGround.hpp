// Copyright(c) 2024 Valkai-Németh Béla-Örs

#ifndef PLAY_GROUND_H
#define PLAY_GROUND_H

#include <vector>
#include "TileEntry.hpp"
#include "AtlassedSpriteU.hpp"
#include "Vector2D.hpp"

class PlayGround
{
	std::vector<TileEntry> m_tiles;
	AtlassedSpriteU m_tileSprite;
	unsigned short m_height{0};
	unsigned short m_width{0};

public:
	PlayGround(unsigned short screenHeight, unsigned short screenWidth, SDL_Renderer* pRenderer, const char* pFilePathToTileAtlas);
	void Init();
	void Draw(float deltaTime);
	unsigned short GetNrOfTiles() const;
	TileEntry& GetTileAt(unsigned short tileId);
	TileEntry& GetTileAt(unsigned short tileX, unsigned short tileY);
	unsigned short GetNeighborsForTileAt(std::array<unsigned short, 4>& neighborIds, unsigned short tileId) const;
};

#endif // PLAY_GROUND_H

