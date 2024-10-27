// Copyright(c) 2024 Valkai-N�meth B�la-�rs

#ifndef BASE_CONTROL_H
#define BASE_CONTROL_H

#include "PlayGround.hpp"
#include "IDrawable.hpp"

#include <functional>

class BaseControl
{
public:
	explicit BaseControl(PlayGround& playGround, unsigned short startTileId);
	BaseControl(const BaseControl&) = delete;
	BaseControl& operator= (const BaseControl&) = delete;
	const vo::Vector2D<float>& GetPos() const;
	const vo::Vector2D<signed short>& GetMoveDir() const;
	void SetMovementSpeed(const float speed);
	virtual void Update(float deltaTime, vo::IDrawable* pDrawable);
	virtual ~BaseControl() = default;

protected:
	PlayGround& m_playGround;

	void Move(const vo::Vector2D<signed short>& dir, float deltaTime);
	unsigned short& GetPotentialTargetId();
	unsigned short& GetCurrentId();
	unsigned short& GetTargetId();

private:
	float (BaseControl::*m_activeStepper)(const float){nullptr};
	vo::Vector2D<float> m_pos{0.f, 0.f};
	vo::Vector2D<signed short> m_moveDir{0, 0};
	float m_movementSpeed{0.14f};
	float m_stepperTarget{0.f};
	unsigned short m_currentTileId{std::numeric_limits<unsigned short>::max()};
	unsigned short m_targetTileId{std::numeric_limits<unsigned short>::max()};
	unsigned short m_potentialTargetTileId{std::numeric_limits<unsigned short>::max()};

	static float StepTowards(float& valToStep, signed short &moveDir, const float target, const float step);
	float StepTowardsX(const float step);
	float StepTowardsY(const float step);
	void UpdateInternal(float step, vo::IDrawable* pDrawable);
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