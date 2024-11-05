// Copyright(c) 2024 Valkai-Németh Béla-Örs

#ifndef BOMB_LOGIC_HPP
#define BOMB_LOGIC_HPP

#include "Sprite.hpp"
#include "SpriteAnimator.hpp"
#include "PlayGround.hpp"

#include <vector>

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

	class BombSharedSprite {
	public:
		BombSharedSprite(const std::shared_ptr<vo::TextureAtlasBase> textureAtlas, const unsigned texId);
		void Update(float deltaTime);
		bool Draw(int posX, int posY);

	private:
		std::shared_ptr<vo::TextureAtlasBase> m_textureAtlas;
		vo::SpriteAnimator<unsigned char> m_fuseAnimator;
		unsigned m_texId;
	};

	class BombEntry : public vo::IDrawable {
	public:
		BombSharedSprite& sharedSprite;
		float timeTillBlastS{1.f};
		unsigned short tileId;
		unsigned short posX{0};
		unsigned short posY{0};

		BombEntry(BombSharedSprite& _sharedSprite, unsigned short _tileId) : sharedSprite(_sharedSprite), tileId(_tileId) {}
		bool Draw(int, int, float) override { return sharedSprite.Draw(posX, posY); };
	};

	vo::SpriteAnimator<unsigned char> m_blastAnimator;
	PlayGround& m_playGround;
	BombSharedSprite m_bombSprite;
	vo::TextureAtlasBase* m_pAtlas;
	std::vector<BombEntry> m_bombs;
};

#endif // BOMB_LOGIC_HPP

