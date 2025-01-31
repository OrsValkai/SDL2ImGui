// Copyright(c) 2024 Valkai-N�meth B�la-�rs

#include "BaseControl.hpp"
#include "Player.hpp"
#include <array>

BaseControl::BaseControl(PlayGround& playGround, unsigned short startTileId) : m_playGround(playGround), m_initialTileId(startTileId) {
	if (startTileId < playGround.GetNrOfTiles())
	{
		Init();
	}
	else {
		throw std::out_of_range("Provided startTileId is out of range!");
	}
}

void BaseControl::Init()
{
	// Make sure starting tile is free
	auto& tileEntry = m_playGround.GetTileAt(m_initialTileId);
	tileEntry.m_flags = 0;

	// Make sure it's neighbours are free too
	std::array<unsigned short, 4> nIds;
	for (unsigned short i = 0; i < m_playGround.GetNeighborIdsForTileAt(nIds, m_initialTileId); i++) {
		auto& nTileEntry = m_playGround.GetTileAt(nIds[i]);

		if (nTileEntry.HasFlagAll(TileEntry::Flags::DestroyableTile))
			nTileEntry.m_flags = 0;
	}

	m_pos.x = tileEntry.posX;
	m_pos.y = tileEntry.posY;

	m_currentTileId = m_initialTileId;
	m_targetTileId = m_initialTileId;
}

const vo::Vector2D<float>& BaseControl::GetPos() const {
	return m_pos;
}

const vo::Vector2D<signed short>& BaseControl::GetMoveDir() const {
	return m_moveDir;
}

void BaseControl::SetMovementSpeed(const float speed) {
	m_movementSpeed = speed;
}

void BaseControl::Reset() {
	m_activeStepper = nullptr;
	m_potentialTargetTileId = std::numeric_limits<unsigned short>::max();
	m_shouldPlaceBomb = false;
	m_moveDir = 0;
	
	Init();
}

void BaseControl::Move(const vo::Vector2D<signed short>& dir, float /*deltaTime*/) {
	if (0 == dir.x && 0 == dir.y) {
		m_potentialTargetTileId = std::numeric_limits<unsigned short>::max();
		return;
	}

	auto nId = m_playGround.GetNeighborIdForTileAt(dir, m_targetTileId);
	if (nId < m_playGround.GetNrOfTiles()) {
		if (nId == m_currentTileId) {
			m_potentialTargetTileId = std::numeric_limits<unsigned short>::max();
			m_currentTileId = m_targetTileId;
			m_targetTileId = nId;
			m_activeStepper = nullptr;
		} else if (!m_playGround.GetTileAt(nId).HasFlagAny(TileEntry::Flags::Occupied)) {
			m_potentialTargetTileId = nId;
		}
	}
}

void BaseControl::PlaceBomb() {
	m_shouldPlaceBomb = true;
}

float BaseControl::StepTowards(float& valToStep, signed short& moveDir, const float target, const float step) {
	float diff = target - valToStep;
	if (float aDiff = std::abs(diff); aDiff > step) {
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
		return step - aDiff;
	}

	return 0.f;
}

float BaseControl::StepTowardsX(const float step) {
	return StepTowards(m_pos.x, m_moveDir.x, m_stepperTarget, step);
}

float BaseControl::StepTowardsY(const float step) {
	return StepTowards(m_pos.y, m_moveDir.y, m_stepperTarget, step * s_ySpeedMultiplier);
}

void BaseControl::PlaceBombInternal(Player* pParent, const TileEntry& tileEntry, const unsigned short tileId) {
	m_shouldPlaceBomb = false;

	if (!tileEntry.HasFlagAny(TileEntry::Flags::Occupied))
		pParent->PlaceBomb(tileId);
}

void BaseControl::UpdateInternal(float step, Player* pParent) {
	auto& curTileEntry = m_playGround.GetTileAt(m_currentTileId);

	if (m_potentialTargetTileId < m_playGround.GetNrOfTiles() && m_targetTileId == m_currentTileId) {
		m_targetTileId = m_potentialTargetTileId;
		m_potentialTargetTileId = std::numeric_limits<unsigned short>::max();
	}

	if (m_targetTileId != m_currentTileId) {
		const auto& targetTileEntry = m_playGround.GetTileAt(m_targetTileId);
		float roundedX = std::roundf(m_pos.x);
		
		// Check death and place bomb for when moving
		if (float roundedY = std::roundf(m_pos.y); roundedX == m_pos.x && roundedY == m_pos.y) {
			if (curTileEntry.HasFlagAny(TileEntry::Flags::HasBlast)) {
				pParent->OnDeath();
			}
			else if (m_shouldPlaceBomb) {
				PlaceBombInternal(pParent, curTileEntry, m_currentTileId);
			}
		}
		else if (targetTileEntry.HasFlagAny(TileEntry::Flags::HasBlast)) {
			pParent->OnDeath();
		}
		else if (m_shouldPlaceBomb) {
			PlaceBombInternal(pParent, targetTileEntry, m_targetTileId);
		}

		// Initialize a new stepper function to execute move with
		if (nullptr == m_activeStepper) {
			float xDiff = std::abs(targetTileEntry.posX - m_pos.x);
			float yDiff = std::abs(targetTileEntry.posY - m_pos.y);

			if (xDiff > yDiff) {
				m_stepperTarget = targetTileEntry.posX;
				m_activeStepper = &BaseControl::StepTowardsX;
				m_moveDir.y = 0;
			} else {
				m_stepperTarget = targetTileEntry.posY;
				m_activeStepper = &BaseControl::StepTowardsY;
				m_moveDir.x = 0;
			}
		}

		// Ececute move
		if (float stepLeft = (this->*m_activeStepper)(step); stepLeft > 0.0001f) {
			// We arrived and had some overflow movement
			// use it for next move if we have one lined up
			m_currentTileId = m_targetTileId;
			m_activeStepper = nullptr;

			UpdateInternal(stepLeft, pParent);
			return;
		}
	} else {
		m_moveDir.x = 0;
		m_moveDir.y = 0;

		// Check death and place bomb for when standing still
		if (curTileEntry.HasFlagAny(TileEntry::Flags::HasBlast)) {
			pParent->OnDeath();
		}
		else if (m_shouldPlaceBomb) {
			PlaceBombInternal(pParent, curTileEntry, m_currentTileId);
		}
	}

	curTileEntry.SubscribeForDraw(pParent, 1);
}

void BaseControl::Update(float deltaTime, Player* pParent) {
	UpdateInternal(m_movementSpeed * deltaTime, pParent);
}
