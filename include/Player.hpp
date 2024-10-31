// Copyright(c) 2024 Valkai-N�meth B�la-�rs

#ifndef PLAYER_H
#define PLAYER_H

#include "TextureAtlasU.hpp"
#include "SpriteAnimator.hpp"
#include "AnimatedSprite.hpp"
#include "BaseControl.hpp"
#include "BombLogic.hpp"

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

class Player : public vo::AnimatedSprite
{
public:
	explicit Player(const std::shared_ptr<vo::TextureAtlasBase> textureAtlas, PlayGround& playGround);
	void SetControl(std::shared_ptr<BaseControl> spCtrl);
	void SetTintColor(Uint8 r, Uint8 g, Uint8 b);
	void Update(float deltaTime);
	bool Draw(int posX, int posY, float deltaTime) override;

private:
	std::shared_ptr<BaseControl> m_pCtrl;
	BombLogic m_bombLogic;
	AnimId m_animId = AnimId::IdleFront;
	Uint8 m_tintR = 255;
	Uint8 m_tintG = 255;
	Uint8 m_tintB = 255;
};

#endif // PLAYER_H

