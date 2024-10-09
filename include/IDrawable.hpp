#ifndef IDRAWABLE_H
#define IDRAWABLE_H

class IDrawable
{
public:
	IDrawable* m_pNextDrawable{nullptr};

	IDrawable& operator=(const IDrawable&) = delete;
	virtual bool Draw(int posX, int posY, float deltaTime) = 0;
	virtual ~IDrawable() = default;
};

#endif // IDRAWABLE_H

