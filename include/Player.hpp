// Copyright(c) 2024 Valkai-Németh Béla-Örs

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
	void PlaceBomb(unsigned int tileId);
	void SetControl(std::shared_ptr<BaseControl> spCtrl);
	void SetTintColor(Uint8 r, Uint8 g, Uint8 b);
	void Update(float deltaTime);
	bool Draw(int posX, int posY, float deltaTime) override;
	void OnDeath();
	void Reset();
	bool IsAlive() const { return m_isAlive; };

private:
	std::shared_ptr<BaseControl> m_pCtrl;
	BombLogic m_bombLogic;
	AnimId m_animId = AnimId::IdleFront;
	Uint8 m_tintR = 255;
	Uint8 m_tintG = 255;
	Uint8 m_tintB = 255;
	bool m_isAlive = true;
};

#endif // PLAYER_H

