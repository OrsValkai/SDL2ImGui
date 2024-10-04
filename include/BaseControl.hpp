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
	virtual void Update(float deltaTime, IDrawable* pDrawable);
	virtual ~BaseControl() = default;

protected:
	PlayGround& m_playGround;

	void MoveBy(float x, float y);

private:
	Vector2D<float> m_pos{0.f,0.f};
	unsigned short m_currentTileId {0};
	unsigned short m_targetTileId {0};
};

#endif // BASE_CONTROL_H