// Copyright(c) 2024 Valkai-N�meth B�la-�rs

#ifndef BOMB_HPP
#define BOMB_HPP

#include "Sprite.hpp"

class Bomb : public vo::Sprite {
public:
	Bomb(const std::shared_ptr<vo::TextureAtlasBase> textureAtlas, const unsigned texId);
};

#endif // BOMB_HPP

