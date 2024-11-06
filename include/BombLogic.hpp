// Copyright(c) 2024 Valkai-Németh Béla-Örs

#ifndef BOMB_LOGIC_HPP
#define BOMB_LOGIC_HPP

#include "Sprite.hpp"
#include "SpriteAnimator.hpp"
#include "PlayGround.hpp"

#include <vector>
#include <array>

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

	static constexpr unsigned char s_MaxBlastLength = 8;
	static constexpr unsigned char s_MaxBombCount = 4;
	inline static float s_BlastTimeSec = 500.f;

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
		inline static BombSharedSprite* s_pSharedSprite{nullptr};

		double counterSec{-1.f};
		unsigned short tileId{std::numeric_limits<unsigned short>::max()};
		signed short posX{0};
		signed short posY{0};

		bool Draw(int, int, float) override { return s_pSharedSprite->Draw(posX, posY); };
	};

	struct BlastEntry {
		signed short posX;
		signed short posY;
		unsigned char type;

		BlastEntry(signed short _posX, signed short _posY, unsigned char _type) : posX(_posX), posY(_posY), type(_type) {}
	};

	void BlastDebugDraw(int posX, int posY, int base);

	vo::SpriteAnimator<unsigned char> m_blastAnimator;
	PlayGround& m_playGround;
	BombSharedSprite m_bombSprite;
	vo::TextureAtlasBase* m_pAtlas;
	std::array<BombEntry, s_MaxBombCount> m_bombs{};
	std::array<std::vector<BlastEntry>, s_MaxBombCount> m_blasts{};
};

#endif // BOMB_LOGIC_HPP

