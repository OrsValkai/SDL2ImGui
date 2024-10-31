// Copyright(c) 2024 Valkai-Németh Béla-Örs

#ifndef VO_SPRITE_H
#define VO_SPRITE_H

#include "TextureAtlasBase.hpp"
#include "IDrawable.hpp"

namespace vo {

	class Sprite : public IDrawable {
	public:
		Sprite(const std::shared_ptr<TextureAtlasBase> textureAtlas, const unsigned texId);
		bool Draw(int posX, int posY, float deltaTime) override;

	private:
		std::shared_ptr<TextureAtlasBase> m_textureAtlas;
		unsigned m_texId;
	};

}

#endif // VO_SPRITE_H

