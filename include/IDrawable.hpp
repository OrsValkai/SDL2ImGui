#ifndef IDRAWABLE_H
#define IDRAWABLE_H

class IDrawable
{
public:
	IDrawable* m_pNextDrawable{nullptr};

	virtual bool Draw(float posX, float posY, float deltaTime) = 0;

	virtual ~IDrawable() = default;
};

#endif // IDRAWABLE_H

