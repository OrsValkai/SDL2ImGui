// Copyright(c) 2024 Valkai-Németh Béla-Örs

#include "BaseControl.hpp"

BaseControl::BaseControl(PlayGround& playGround, unsigned short startTileId) : m_playGround(playGround) {
	if (startTileId < playGround.GetNrOfTiles())
	{
		m_currentTileId = startTileId;
		m_targetTileId = m_currentTileId;
	}
}

const Vector2D<float>& BaseControl::GetPos() const {
	return m_pos;
}

void BaseControl::Update(float deltaTime, IDrawable* pDrawable) {
	auto& tileEntry = m_playGround.GetTileAt(m_currentTileId);
	tileEntry.m_flags = 0;
	tileEntry.pDrawable = pDrawable;

	m_pos.x = tileEntry.posX;
	m_pos.y = tileEntry.posY;
}