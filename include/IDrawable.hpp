#ifndef VO_IDRAWABLE_H
#define VO_IDRAWABLE_H

namespace vo {

	class IDrawable
	{
	public:
		IDrawable* m_pNextDrawable{nullptr};
		unsigned int m_layerId{0};

		IDrawable& operator=(const IDrawable&) = delete;
		virtual bool Draw(int posX, int posY, float deltaTime) = 0;
		virtual ~IDrawable() = default;
	};

}

#endif // VO_IDRAWABLE_H

