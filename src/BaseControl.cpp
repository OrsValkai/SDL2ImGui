// Copyright(c) 2024 Valkai-Németh Béla-Örs

#include "BaseControl.hpp"

BaseControl::BaseControl(PlayGround& playGround, unsigned short startTileId) : m_playGround(playGround) {
	if (startTileId < playGround.GetNrOfTiles())
	{
		auto& tileEntry = m_playGround.GetTileAt(startTileId);
		tileEntry.m_flags = 0;

		m_pos.x = tileEntry.posX;
		m_pos.y = tileEntry.posY;

		m_currentTileId = startTileId;
	}
}

const Vector2D<float>& BaseControl::GetPos() const {
	return m_pos;
}

void BaseControl::Move(const Vector2D<signed short>& dir, float deltaTime) {
	if (0 == dir.x && 0 == dir.y)
		return;

	auto nId = m_playGround.GetNeighborIdForTileAt(dir, m_currentTileId);

	if (nId < m_playGround.GetNrOfTiles()) {
		

		auto& tileEntry = m_playGround.GetTileAt(nId);
		if (tileEntry.HasFlagAny(TileEntry::Flags::Destroyable) || !tileEntry.HasFlagAny(TileEntry::Flags::Occupied)) {
			tileEntry.m_flags = 0;

			m_currentTileId = nId;

			m_pos.x = tileEntry.posX;
			m_pos.y = tileEntry.posY;
		}
	}
}

void BaseControl::Update(float deltaTime, IDrawable* pDrawable) {
	auto& tileEntry = m_playGround.GetTileAt(m_currentTileId);
	tileEntry.pDrawable = pDrawable;
}