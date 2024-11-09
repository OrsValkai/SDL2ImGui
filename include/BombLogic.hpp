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
	static constexpr unsigned char s_Horizontal = 0;
	static constexpr unsigned char s_HorizontalEnd = 1;
	static constexpr unsigned char s_Middle = 2;
	static constexpr unsigned char s_Vertical = 3;
	static constexpr unsigned char s_VerticalEnd = 4;

	static constexpr std::array<unsigned char, 5> s_coreIds{22, 24, 15, 21, 23};

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
		unsigned short drawTileId{0};
		signed short posX{0};
		signed short posY{0};

		bool Draw(int, int, float) override { return s_pSharedSprite->Draw(posX, posY); };
	};

	struct BlastEntry {
		signed short posX;
		signed short posY;
		unsigned char typeId;
		unsigned char angle;

		BlastEntry(signed short _posX, signed short _posY, unsigned char _typeId, unsigned char _angle) : posX(_posX), posY(_posY), typeId(_typeId), angle(_angle) {}
	};

	struct BlastDrawHelper {
		unsigned char typeId;
		unsigned char angle;

		BlastDrawHelper(unsigned char _typeId, unsigned char _angle) : typeId(_typeId), angle(_angle) {}
	};

	void CreateBlast(BombEntry& bE, std::vector<BlastEntry>& blast);
	void BlastDebugDraw(int posX, int posY, int base);

	vo::SpriteAnimator<unsigned char> m_blastAnimator;
	PlayGround& m_playGround;
	BombSharedSprite m_bombSprite;
	vo::TextureAtlasBase* m_pAtlas;
	std::array<BombEntry, s_MaxBombCount> m_bombs{};
	std::array<std::vector<BlastEntry>, s_MaxBombCount> m_blasts{};
	unsigned char m_blastLen{2};
};

#endif // BOMB_LOGIC_HPP

