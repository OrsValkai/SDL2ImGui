// Copyright(c) 2024 Valkai-Németh Béla-Örs

#ifndef BOMB_LOGIC_HPP
#define BOMB_LOGIC_HPP

#include "Sprite.hpp"
#include "SpriteAnimator.hpp"
#include "PlayGround.hpp"

#include <vector>

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
	void PlaceBomb(unsigned int tileId);
	void Update(float deltaTime);
	bool Draw(int posX, int posY, float deltaTime) override;

private:
	static constexpr unsigned char s_Middle = 2;
	static constexpr unsigned char s_Horizontal = 0;
	static constexpr unsigned char s_Vertical = 3;
	static constexpr unsigned char s_HorizontalEnd = 1;
	static constexpr unsigned char s_VerticalEnd = 4;

	static constexpr unsigned char s_MiddleCore = 15;
	static constexpr unsigned char s_HorizontalCore = 22;
	static constexpr unsigned char s_VerticalCore = 21;
	static constexpr unsigned char s_HorizontalEndCore = 24;
	static constexpr unsigned char s_VerticalEndCore = 23;

	static constexpr unsigned char s_MaxNrOfBombs = 4;

	struct BombEntry {
		float timeTillBlastS{1.f};
		unsigned short drawTileId;
		unsigned short tileId;

		BombEntry(unsigned short _drawTileId, unsigned short _tileId) : drawTileId(_drawTileId), tileId(_tileId) {}
	};

	vo::SpriteAnimator<unsigned char> m_blastAnimator;
	PlayGround& m_playGround;
	BombSprite m_bombSprite;
	vo::TextureAtlasBase* m_pAtlas;
	std::vector<BombEntry> m_bombs;
};

#endif // BOMB_LOGIC_HPP

