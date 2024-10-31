// Copyright(c) 2024 Valkai-Németh Béla-Örs

#ifndef VO_ANIMATED_SPRITE_H
#define VO_ANIMATED_SPRITE_H

#include "TextureAtlasBase.hpp"
#include "SpriteAnimator.hpp"
#include "IDrawable.hpp"

namespace vo {

	class AnimatedSprite : public IDrawable, public SpriteAnimator<unsigned char> {
	public:
		AnimatedSprite(const std::shared_ptr<TextureAtlasBase> textureAtlas, const int targetFPS);

		bool Draw(int posX, int posY, float deltaTime) override;

	protected:
		TextureAtlasBase* GetTextureAtlas();

	private:
		std::shared_ptr<TextureAtlasBase> m_textureAtlas;
	};

	// Implementation
	inline TextureAtlasBase* AnimatedSprite::GetTextureAtlas() {
		return m_textureAtlas.get();
	}
}

#endif // ANIMATED_SPRITE_H

