// Copyright(c) 2024 Valkai-Németh Béla-Örs

#ifndef BOMB_LOGIC_HPP
#define BOMB_LOGIC_HPP

#include "Sprite.hpp"
#include "SpriteAnimator.hpp"
#include "PlayGround.hpp"

class BombLogic : public vo::Sprite {
public:
	BombLogic(PlayGround& playGround, const unsigned texId);
	void Update(float deltaTime);
	bool Draw(int posX, int posY, float deltaTime) override;

private:
	vo::SpriteAnimator<unsigned char> m_blastAnimator;
	vo::SpriteAnimator<unsigned char> m_fuseAnimator;
	PlayGround& m_playGround;
};

#endif // BOMB_LOGIC_HPP

