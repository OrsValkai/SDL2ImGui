// Copyright(c) 2024 Valkai-Németh Béla-Örs

#ifndef PLAYER_H
#define PLAYER_H

#include "PlayerSprite.hpp"
#include "IDrawable.hpp"

class Player : public IDrawable
{
private:
	PlayerSprite m_sprite;

public:
	Player(SDL_Renderer* pRenderer, const char* pFilePath, unsigned width, unsigned height, unsigned nrSprites);
	bool Draw(float posX, float posY, float deltaTime) final;
};

#endif // PLAYER_H

