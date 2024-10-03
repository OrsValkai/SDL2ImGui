// Copyright(c) 2024 Valkai-Németh Béla-Örs

#include "PlayGround.hpp"
#include "TileEntry.inl"
#include "IDrawable.hpp"

PlayGround::PlayGround(unsigned short screenHeight, unsigned short screenWidth, SDL_Renderer* pRenderer, const char* pFilePathToTileAtlas)
	: m_tileSprite(pRenderer, pFilePathToTileAtlas, 64, 90, 2) {
	//: m_tileSprite(pRenderer, "", 64, 56, 2) {
	m_height = screenHeight / TileEntry::Height;
	m_width = screenWidth / TileEntry::Width;

	Init();
}

void PlayGround::Init() {
	Vector2D<signed short> posOffset = { 0, 0 };

	if (0 == m_height % 2)
		m_height--;

	if (0 == m_width % 2) {
		m_width--;
		posOffset.x += TileEntry::Width / 2;
	}

	m_tiles.resize(static_cast<size_t>(m_height) * m_width);
	if (m_tiles.capacity() >= std::numeric_limits<unsigned short>::max())
		throw std::overflow_error("This was designed to be below, if really needed change type from unsigned short!");

	for (size_t i = 0; i < m_width; ++i) {
		for (size_t j = 0; j < m_height; ++j) {
			auto& tile = m_tiles[j * m_width + i];

			if ((0 != i % 2) && (0 != j % 2)) {
				tile.SetFlag(TileEntry::Flags::OccupiedByTile);
			}
			else {
				tile.SetFlag(TileEntry::Flags::DestroyableTile);
			}

			tile.posX = static_cast<signed short>(i * TileEntry::Width + posOffset.x);
			tile.posY = static_cast<signed short>((j * TileEntry::Height) + posOffset.y);
		}
	}
}

void PlayGround::Draw(float deltaTime) {
	for (auto& tile : m_tiles) {
		if (tile.HasFlagAny(TileEntry::Flags::OccupiedByTile)) {
			m_tileSprite.Draw(tile.posX, tile.posY, tile.HasFlagAny(TileEntry::Flags::Destroyable));
		}

		while (tile.pDrawable) {
			IDrawable* pCurrent = tile.pDrawable;

			pCurrent->Draw(tile.posX, tile.posY, deltaTime);
			tile.pDrawable = pCurrent->m_pNextDrawable;
			pCurrent->m_pNextDrawable = nullptr;
		}
	}
}

unsigned short PlayGround::GetNrOfTiles() const {
	return static_cast<unsigned short>(m_tiles.size());
}

TileEntry& PlayGround::GetTileAt(unsigned short tileId) {
	return m_tiles[tileId];
}

unsigned short PlayGround::GetTileId(unsigned short tileX, unsigned short tileY) const {
	auto tY = static_cast<size_t>(tileX);
	tY *= m_width;

	return static_cast<unsigned short>(tY + tileY);
}

TileEntry& PlayGround::GetTileAt(unsigned short tileX, unsigned short tileY)
{
	auto tY = static_cast<size_t>(tileX);
	tY *= m_width;

	return m_tiles[tY + tileY];
}

unsigned short PlayGround::GetNeighborsForTileAt(std::array<unsigned short, 4>& neighborIds, unsigned short tileId) const {
	return 0;
}