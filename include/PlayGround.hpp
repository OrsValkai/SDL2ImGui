// Copyright(c) 2024 Valkai-Németh Béla-Örs

#ifndef PLAY_GROUND_H
#define PLAY_GROUND_H

#include "TileEntry.hpp"
#include "TextureAtlasU.hpp"
#include "Vector2D.hpp"

#include <vector>

class PlayGround
{
public:
	PlayGround(unsigned short screenWidth, unsigned short screenHeight, const std::shared_ptr<vo::TextureAtlasU> textureAtlas);
	void Init();
	void Draw(float deltaTime);
	unsigned short GetNrOfTiles() const;
	unsigned short GetTileId(unsigned short tileX, unsigned short tileY) const;
	TileEntry& GetTileAt(unsigned short tileId);
	TileEntry& GetTileAt(unsigned short tileX, unsigned short tileY);
	unsigned short GetNeighborIdForTileAt(const vo::Vector2D<signed short>& direction, unsigned short tileId) const;
	unsigned short GetNeighborIdsForTileAt(std::array<unsigned short, 4>& neighborIds, unsigned short tileId) const;
	unsigned short GetNeighborIdForTileAt(const vo::Vector2D<signed short>& direction, unsigned short tileX, unsigned short tileY) const;
	unsigned short GetNeighborIdsForTileAt(std::array<unsigned short, 4>& neighborIds, unsigned short tileX, unsigned short tileY) const;
	std::shared_ptr<vo::TextureAtlasBase> GetAtlas() const;
	vo::Vector2D<signed short>& GetPosOffset() const;
	void SubScribeToPostDraw(vo::IDrawable* pDrawable);
	void SubScribeToPreDraw(vo::IDrawable* pDrawable);

private:
	std::vector<TileEntry> m_tiles;
	std::shared_ptr<vo::TextureAtlasU> m_pTileTextureAtlas;
	vo::IDrawable* m_pPostDraw{nullptr};
	vo::IDrawable* m_pPreDraw{nullptr};
	vo::Vector2D<signed short> m_posOffset{ 0,0 };
	unsigned short m_height{0};
	unsigned short m_width{0};

	static void DrawSubscribed(vo::IDrawable** pDrawable, int posX, int posY, float deltaTime);
};

#endif // PLAY_GROUND_H

