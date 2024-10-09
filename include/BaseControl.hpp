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
	const Vector2D<int>& GetPos() const;
	virtual void Update(float deltaTime, IDrawable* pDrawable);
	virtual ~BaseControl() = default;

protected:
	PlayGround& m_playGround;

	void Move(const Vector2D<signed short>& dir, float deltaTime);

private:
	Vector2D<int> m_pos{0, 0};
	unsigned short m_currentTileId{0};
};

#endif // BASE_CONTROL_H