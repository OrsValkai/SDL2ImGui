// Copyright(c) 2024 Valkai-Németh Béla-Örs

#include "Bomb.hpp"

Bomb::Bomb(const std::shared_ptr<vo::TextureAtlasBase> textureAtlas, const unsigned texId)
	: vo::Sprite(textureAtlas, texId) {
}
