// Copyright(c) 2024 Valkai-Németh Béla-Örs

#include "BaseControl.hpp"
#include <array>

BaseControl::BaseControl(PlayGround& playGround, unsigned short startTileId) : m_playGround(playGround) {
	if (startTileId < playGround.GetNrOfTiles())
	{
		auto& tileEntry = m_playGround.GetTileAt(startTileId);
		tileEntry.m_flags = 0;

		m_pos.x = tileEntry.posX;
		m_pos.y = tileEntry.posY;

		m_currentTileId = startTileId;
		m_targetTileId = startTileId;
	}
}

const Vector2D<float>& BaseControl::GetPos() const {
	return m_pos;
}

const Vector2D<signed short>& BaseControl::GetMoveDir() const {
	return m_moveDir;
}

void BaseControl::Move(const Vector2D<signed short>& dir, float /*deltaTime*/) {
	if (0 == dir.x && 0 == dir.y) {
		m_potentialTargetTileId = std::numeric_limits<unsigned short>::max();
		return;
	}

	auto nId = m_playGround.GetNeighborIdForTileAt(dir, m_targetTileId);
	if (nId < m_playGround.GetNrOfTiles()) {
		const auto& tileEntry = m_playGround.GetTileAt(nId);
		if (tileEntry.HasFlagAny(TileEntry::Flags::Destroyable) || !tileEntry.HasFlagAny(TileEntry::Flags::Occupied)) {
			if (nId == m_currentTileId) {
				m_potentialTargetTileId = std::numeric_limits<unsigned short>::max();
				m_targetTileId = m_currentTileId;
			} else {
				m_potentialTargetTileId = nId;
			}
		}
	}
}

static inline bool BaseControl_StepTowards(float& valToStep, signed short& moveDir, const float diff, const float step, float target) {
	if (std::abs(diff) > step) {
		if (diff >= 0.f) {
			valToStep += step;
			moveDir = 1;
		}
		else {
			valToStep -= step;
			moveDir = -1;
		}
	}
	else {
		valToStep = target;
		return true;
	}

	return false;
}

void BaseControl::Update(float deltaTime, IDrawable* pDrawable) {
	const auto& curTileEntry = m_playGround.GetTileAt(m_currentTileId);
	float targetX = curTileEntry.posX;
	float targetY = curTileEntry.posY;

	if (m_potentialTargetTileId < m_playGround.GetNrOfTiles() && m_targetTileId == m_currentTileId) {
		m_targetTileId = m_potentialTargetTileId;
		m_potentialTargetTileId = std::numeric_limits<unsigned short>::max();

		m_moveDir.x = 0;
		m_moveDir.y = 0;
	}

	if (m_targetTileId != m_currentTileId) {
		auto& targetTileEntry = m_playGround.GetTileAt(m_targetTileId);

		targetTileEntry.m_flags = 0;

		targetX = targetTileEntry.posX;
		targetY = targetTileEntry.posY;
	} else {
		m_moveDir.x = 0;
		m_moveDir.y = 0;
	}
	
	float diffX = targetX - m_pos.x;
	float diffY = targetY - m_pos.y;

	if (float stepAmount = deltaTime * 0.1f; BaseControl_StepTowards(m_pos.x, m_moveDir.x, diffX, stepAmount, targetX)
		&& BaseControl_StepTowards(m_pos.y, m_moveDir.y, diffY, stepAmount, targetY)) {

		m_currentTileId = m_targetTileId;
	}

	auto& tileEntry = m_playGround.GetTileAt(m_currentTileId);
	tileEntry.pDrawable = pDrawable;
}