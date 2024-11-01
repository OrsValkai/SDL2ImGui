// Copyright(c) 2024 Valkai-Németh Béla-Örs

#include "PlayGround.hpp"
#include "IDrawable.hpp"
#include <array>

PlayGround::PlayGround(unsigned short screenWidth, unsigned short screenHeight, const std::shared_ptr<vo::TextureAtlasU> textureAtlas)
	: m_pTileTextureAtlas(textureAtlas) {
	m_height = screenHeight / TileEntry::Height;
	m_width = screenWidth / TileEntry::Width;

	Init();
}

void PlayGround::Init() {
	m_posOffset.x = 0;
	m_posOffset.y = 0;

	if (0 == m_height % 2) {
		m_height-=3;
		m_posOffset.y += TileEntry::Height + TileEntry::Height / 2;
	} else {
		m_height-=2;
		m_posOffset.y += TileEntry::Height;
	}

	if (0 == m_width % 2) {
		m_width--;
		m_posOffset.x += TileEntry::Width / 2;
	}

	m_tiles.resize(static_cast<size_t>(m_height) * m_width);
	if (m_tiles.capacity() >= std::numeric_limits<unsigned short>::max())
		throw std::overflow_error("This was designed to be below, if really needed change type from unsigned short!");

	for (size_t i = 0; i < m_width; ++i) {
		for (size_t j = 0; j < m_height; ++j) {
			auto& tile = m_tiles[j * m_width + i];

			tile.m_flags = 0;
			if ((0 != i % 2) && (0 != j % 2)) {
				tile.SetFlag(TileEntry::Flags::OccupiedByTile);
			} else {
				tile.SetFlag(TileEntry::Flags::DestroyableTile);
			}

			tile.posX = static_cast<signed short>(i * TileEntry::Width + m_posOffset.x);
			tile.posY = static_cast<signed short>((j * TileEntry::Height) + m_posOffset.y);
		}
	}
}

void PlayGround::Draw(float deltaTime) {
	DrawSubscribed(&m_pPreDraw, m_posOffset.x, m_posOffset.y, deltaTime);

	for (auto& tile : m_tiles) {
		if (tile.HasFlagAny(TileEntry::Flags::OccupiedByTile)) {
			unsigned int tileType = tile.HasFlagAny(TileEntry::Flags::Destroyable) ? 0 : 1;
			m_pTileTextureAtlas->DrawDoubleHeight(tile.posX, tile.posY, 46 + tileType);
		}

		DrawSubscribed(&tile.pDrawable, tile.posX, tile.posY, deltaTime);
	}

	DrawSubscribed(&m_pPostDraw, m_posOffset.x, m_posOffset.y, deltaTime);
}

unsigned short PlayGround::GetNrOfTiles() const {
	return static_cast<unsigned short>(m_tiles.size());
}

TileEntry& PlayGround::GetTileAt(unsigned short tileId) {
	return m_tiles[tileId];
}

unsigned short PlayGround::GetTileId(unsigned short tileX, unsigned short tileY) const {
	if (tileX >= m_width || tileY >= m_height)
		return static_cast<unsigned short>(m_tiles.size());
	
	auto tY = static_cast<size_t>(tileY);
	tY *= m_width;

	return static_cast<unsigned short>(tY + tileX);
}

TileEntry& PlayGround::GetTileAt(unsigned short tileX, unsigned short tileY)
{
	return m_tiles[GetTileId(tileX, tileY)];
}

unsigned short PlayGround::GetNeighborIdForTileAt(const vo::Vector2D<signed short>& direction, unsigned short tileId) const {
	unsigned short tileX = tileId % m_width;
	unsigned short tileY = tileId / m_width;

	return GetNeighborIdForTileAt(direction, tileX, tileY);
}

unsigned short PlayGround::GetNeighborIdsForTileAt(std::array<unsigned short, 4>& neighborIds, unsigned short tileId) const {
	std::array<vo::Vector2D<signed short>, 4> dirs{{{1, 0}, {-1, 0}, {0, 1}, {0, -1}}};
	unsigned short count = 0;

	for (const auto& dir : dirs) {
		neighborIds[count] = GetNeighborIdForTileAt(dir, tileId);
		if (neighborIds[count] < m_tiles.size())
			count++;
	}

	return count;
}

unsigned short PlayGround::GetNeighborIdForTileAt(const vo::Vector2D<signed short>& direction, unsigned short tileX, unsigned short tileY) const {
	tileX += direction.x;
	tileY += direction.y;

	return GetTileId(tileX, tileY);
}

unsigned short PlayGround::GetNeighborIdsForTileAt(std::array<unsigned short, 4>& neighborIds, unsigned short tileX, unsigned short tileY) const {
	std::array<vo::Vector2D<signed short>, 4> dirs{ {{1, 0}, {-1, 0}, {0, 1}, {0, -1}} };
	unsigned short count = 0;

	for (const auto& dir : dirs) {
		neighborIds[count] = GetNeighborIdForTileAt(dir, tileX, tileY);
		if (neighborIds[count] < m_tiles.size())
			count++;
	}

	return count;
}

std::shared_ptr<vo::TextureAtlasBase> PlayGround::GetAtlas() const {
	return m_pTileTextureAtlas;
}

vo::Vector2D<signed short>& PlayGround::GetPosOffset() const {
	m_posOffset;
}

void PlayGround::SubScribeToPostDraw(vo::IDrawable* pDrawable) {
	if (nullptr == pDrawable)
		return;

	if (nullptr == m_pPostDraw)
		m_pPostDraw = pDrawable;
	else {
		pDrawable->m_pNextDrawable = m_pPostDraw;
		m_pPostDraw = pDrawable;
	}
}

void PlayGround::SubScribeToPreDraw(vo::IDrawable* pDrawable) {
	if (nullptr == pDrawable)
		return;

	if (nullptr == m_pPreDraw)
		m_pPreDraw = pDrawable;
	else {
		pDrawable->m_pNextDrawable = m_pPreDraw;
		m_pPreDraw = pDrawable;
	}
}

void PlayGround::DrawSubscribed(vo::IDrawable** pDrawable, int posX, int posY, float deltaTime) {
	while (*pDrawable) {
		vo::IDrawable* pCurrent = *pDrawable;

		pCurrent->Draw(posX, posY, deltaTime);
		*pDrawable = pCurrent->m_pNextDrawable;
		pCurrent->m_pNextDrawable = nullptr;
	}
}
