// Copyright(c) 2024 Valkai-Németh Béla-Örs

#ifndef BASE_CONTROL_H
#define BASE_CONTROL_H

#include "PlayGround.hpp"

class BaseControl
{
public:
	explicit BaseControl(PlayGround& playGround, unsigned short startTileId);
	BaseControl(const BaseControl&) = delete;
	BaseControl& operator= (const BaseControl&) = delete;
	const Vector2D<float>& GetPos() const;
	const Vector2D<signed short>& GetMoveDir() const;
	virtual void Update(float deltaTime, IDrawable* pDrawable);
	virtual ~BaseControl() = default;

protected:
	PlayGround& m_playGround;

	void Move(const Vector2D<signed short>& dir, float deltaTime);

private:
	Vector2D<float> m_pos{0.f, 0.f};
	Vector2D<signed short> m_moveDir{0, 0};
	unsigned short m_currentTileId{std::numeric_limits<unsigned short>::max()};
	unsigned short m_targetTileId{std::numeric_limits<unsigned short>::max()};
	unsigned short m_potentialTargetTileId{std::numeric_limits<unsigned short>::max()};
};

#endif // BASE_CONTROL_H