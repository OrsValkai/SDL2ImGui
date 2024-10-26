// Copyright(c) 2024 Valkai-Németh Béla-Örs

#include "AnimatedSprite.hpp"

namespace vo {

	AnimatedSprite::AnimatedSprite(const std::shared_ptr<TextureAtlasBase> textureAtlas, const int targetFPS)
		: SpriteAnimator(targetFPS)
		, m_textureAtlas(textureAtlas) {
	}

	bool AnimatedSprite::Draw(int posX, int posY, float deltaTime) {

		return m_textureAtlas->Draw(posX, posY, 0, 0, SDL_FLIP_NONE);
	}

}