// Copyright(c) 2024 Valkai-Németh Béla-Örs

#include "Sprite.hpp"

namespace vo {

	Sprite::Sprite(const std::shared_ptr<TextureAtlasBase> textureAtlas, const unsigned texId)
		: m_textureAtlas(textureAtlas)
		, m_texId(texId) {
	}

	bool Sprite::Draw(int posX, int posY, float deltaTime) {
		return m_textureAtlas->Draw(posX, posY, m_texId, 0, SDL_FLIP_NONE);
	}

}