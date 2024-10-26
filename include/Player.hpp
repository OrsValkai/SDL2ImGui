// Copyright(c) 2024 Valkai-Németh Béla-Örs

#ifndef PLAYER_H
#define PLAYER_H

#include "TextureAtlasU.hpp"
#include "SpriteAnimator.hpp"
#include "AnimatedSprite.hpp"
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

class Player : public vo::AnimatedSprite
{
public:
	explicit Player(const std::shared_ptr<vo::TextureAtlasBase> textureAtlas);
	void SetControl(std::shared_ptr<BaseControl> spCtrl);
	void Update(float deltaTime);
	bool Draw(int posX, int posY, float deltaTime) override;

private:
	std::shared_ptr<BaseControl> m_pCtrl;
	AnimId m_animId = AnimId::IdleBack;
};

#endif // PLAYER_H

