// Copyright(c) 2024 Valkai-Németh Béla-Örs

#ifndef BOMB_LOGIC_HPP
#define BOMB_LOGIC_HPP

#include "Sprite.hpp"
#include "SpriteAnimator.hpp"
#include "PlayGround.hpp"

class BombSprite : public vo::Sprite {
public:
	BombSprite(const std::shared_ptr<vo::TextureAtlasBase> textureAtlas, const unsigned texId);
	bool Draw(int posX, int posY, float deltaTime) override;

private:
	vo::SpriteAnimator<unsigned char> m_fuseAnimator;
};

class BombLogic : public vo::IDrawable {
public:
	BombLogic(PlayGround& playGround, const unsigned texId);
	void Update(float deltaTime);
	bool Draw(int posX, int posY, float deltaTime) override;

private:
	vo::SpriteAnimator<unsigned char> m_blastAnimator;
	PlayGround& m_playGround;
	BombSprite m_bomb;
	vo::TextureAtlasBase* m_pAtlas;
};

#endif // BOMB_LOGIC_HPP

