// Copyright(c) 2024 Valkai-Németh Béla-Örs

#ifndef PLAYER_H
#define PLAYER_H

#include "TextureAtlasU.hpp"
#include "SpriteAnimator.hpp"
#include "IDrawable.hpp"
#include "BaseControl.hpp"

enum class AnimId : unsigned char
{
	IdleBack = 0,
	IdleRight,
	IdleFront,
	IdleLeft,
	WalkBack,
	WalkRight,
	WalkFront,
	WalkLeft,
	AnimIdsCount
};

class Player : public vo::IDrawable, public vo::SpriteAnimator<unsigned char>
{
private:
	std::shared_ptr<vo::TextureAtlasU> m_textureAtlas;
	std::shared_ptr<BaseControl> m_pCtrl;
	AnimId m_animId = AnimId::IdleBack;

	void InitAnimator();

public:
	Player(SDL_Renderer* pRenderer, const char* pFilePath, unsigned width, unsigned height, unsigned nrSprites);
	Player(SDL_Renderer* pRenderer, SDL_Surface& surface, unsigned nrSprites);
	std::shared_ptr<BaseControl> AddControl(std::shared_ptr<BaseControl> spCtrl);
	void Update(float deltaTime);
	bool Draw(int posX, int posY, float deltaTime) override;
};

#endif // PLAYER_H

