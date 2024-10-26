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

const vo::Vector2D<float>& BaseControl::GetPos() const {
	return m_pos;
}

const vo::Vector2D<signed short>& BaseControl::GetMoveDir() const {
	return m_moveDir;
}

void BaseControl::SetMovementSpeed(const float speed)
{
	m_movementSpeed = speed;
}

void BaseControl::Move(const vo::Vector2D<signed short>& dir, float /*deltaTime*/) {
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
				m_currentTileId = m_targetTileId;
				m_targetTileId = nId;
				m_activeStepper = nullptr;
			} else {
				m_potentialTargetTileId = nId;
			}
		}
	}
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
	return StepTowards(m_pos.y, m_moveDir.y, m_stepperTarget, step);
}

void BaseControl::UpdateInternal(float step, vo::IDrawable* pDrawable) {
	auto& curTileEntry = m_playGround.GetTileAt(m_currentTileId);

	if (m_potentialTargetTileId < m_playGround.GetNrOfTiles() && m_targetTileId == m_currentTileId) {
		m_targetTileId = m_potentialTargetTileId;
		m_potentialTargetTileId = std::numeric_limits<unsigned short>::max();
	}

	if (m_targetTileId != m_currentTileId) {
		auto& targetTileEntry = m_playGround.GetTileAt(m_targetTileId);

		targetTileEntry.m_flags = 0;

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

		float stepLeft = (this->*m_activeStepper)(step);
		if (stepLeft > 0.0001f) {
			m_currentTileId = m_targetTileId;
			m_activeStepper = nullptr;

			UpdateInternal(stepLeft, pDrawable);
			return;
		}
	} else {
		m_moveDir.x = 0;
		m_moveDir.y = 0;
	}

	if (nullptr == curTileEntry.pDrawable)
		curTileEntry.pDrawable = pDrawable;
	else {
		pDrawable->m_pNextDrawable = curTileEntry.pDrawable;
		curTileEntry.pDrawable = pDrawable;
	}
}

void BaseControl::Update(float deltaTime, vo::IDrawable* pDrawable) {
	UpdateInternal(m_movementSpeed * deltaTime, pDrawable);
}
