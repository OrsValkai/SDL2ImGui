// Copyright(c) 2024 Valkai-Németh Béla-Örs

#ifndef BASE_CONTROL_H
#define BASE_CONTROL_H

#include "PlayGround.hpp"
#include <functional>

class Player;

class BaseControl
{
public:
	explicit BaseControl(PlayGround& playGround, unsigned short startTileId);
	BaseControl(const BaseControl&) = delete;
	BaseControl& operator= (const BaseControl&) = delete;
	const vo::Vector2D<float>& GetPos() const;
	const vo::Vector2D<signed short>& GetMoveDir() const;
	void SetMovementSpeed(const float speed);
	virtual void Update(float deltaTime, Player* parent);
	virtual ~BaseControl() = default;

protected:
	PlayGround& m_playGround;

	void Move(const vo::Vector2D<signed short>& dir, float deltaTime);
	void PlaceBomb();
	unsigned short& GetPotentialTargetId();
	unsigned short& GetCurrentId();
	unsigned short& GetTargetId();

private:
	float (BaseControl::*m_activeStepper)(const float){nullptr};
	vo::Vector2D<float> m_pos{0.f, 0.f};
	vo::Vector2D<signed short> m_moveDir{0, 0};
	float m_movementSpeed{0.14f};
	float m_stepperTarget{0.f};
	unsigned short m_currentTileId{0};
	unsigned short m_targetTileId{0};
	unsigned short m_potentialTargetTileId{std::numeric_limits<unsigned short>::max()};
	bool m_shouldPlaceBomb{false};

	static constexpr float s_ySpeedMultiplier = static_cast<float>(TileEntry::Height) / static_cast<float>(TileEntry::Width);
	static float StepTowards(float& valToStep, signed short &moveDir, const float target, const float step);
	float StepTowardsX(const float step);
	float StepTowardsY(const float step);
	void PlaceBombInternal(Player* pParent, const TileEntry& tileEntry, const unsigned short tileId);
	void UpdateInternal(float step, Player* parent);
};

// Implementation
inline unsigned short& BaseControl::GetPotentialTargetId() {
	return m_potentialTargetTileId;
}

inline unsigned short& BaseControl::GetCurrentId() {
	return m_currentTileId;
}

inline unsigned short& BaseControl::GetTargetId() {
	return m_targetTileId;
}

#endif // BASE_CONTROL_H