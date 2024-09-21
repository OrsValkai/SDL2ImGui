// Copyright(c) 2024 Valkai-Németh Béla-Örs

#include "PlayGround.hpp"
#include "TileEntry.inl"

PlayGround::PlayGround(unsigned int screenHeight, unsigned int screenWidth, SDL_Renderer* pRenderer, const char* pFilePathToTileAtlas)
	: m_tileSprite(pRenderer, pFilePathToTileAtlas, 64, 90, 2) {
	m_height = screenHeight / TileEntry::VisualHeight;
	m_width = screenWidth / TileEntry::VisualWidth;

	Init();
}

void PlayGround::Init() {
	signed short posOffsetX = 0;
	signed short posOffsetY = 0;

	if (0 == m_height % 2)
		m_height--;

	if (0 == m_width % 2) {
		m_width--;
		posOffsetX += TileEntry::VisualWidth / 2;
	}

	m_tiles.resize(m_height * m_width);

	for (size_t i = 0; i < m_width; ++i) {
		for (size_t j = 0; j < m_height; ++j) {
			auto& tile = m_tiles[i * m_height + j];

			if ((0 != i % 2) && (0 != j % 2)) {
				tile.SetFlag(TileEntry::Flags::OccupiedByTile);
			}
			else {
				//tile.SetFlag(TileEntry::Flags::DestroyableTile);
			}

			tile.posX = static_cast<signed short>(i * TileEntry::VisualWidth + posOffsetX);
			tile.posY = static_cast<signed short>((j * TileEntry::VisualHeight) + posOffsetY);
		}
	}
}

void PlayGround::Draw(float) {
	for (const auto& tile : m_tiles) {
		if (tile.HasFlagAny(TileEntry::Flags::OccupiedByTile)) {
			m_tileSprite.Draw(tile.posX, tile.posY, tile.HasFlagAny(TileEntry::Flags::Destroyable) ? 1 : 0);
		}
	}
}