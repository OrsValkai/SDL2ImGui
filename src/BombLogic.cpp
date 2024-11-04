// Copyright(c) 2024 Valkai-Németh Béla-Örs

#include "BombLogic.hpp"

BombSprite::BombSprite(const std::shared_ptr<vo::TextureAtlasBase> textureAtlas, const unsigned texId)
	: Sprite(textureAtlas, texId)
	, m_fuseAnimator(20) {

	m_fuseAnimator.SetSpriteIdPattern({ 0, 1, 2, 3, 4 });
	m_fuseAnimator.AddAnimOffset(16);
}

bool BombSprite::Draw(int posX, int posY, float deltaTime) {
	posY += 32;
	
	auto retVal = vo::Sprite::Draw(posX, posY, deltaTime);
	GetTextureAtlas()->Draw(posX-24, posY-20, m_fuseAnimator.ComputeSpriteId(0, deltaTime));

	return retVal;
}

BombLogic::BombLogic(PlayGround& playGround, const unsigned texId)
	: m_blastAnimator(20)
	, m_playGround(playGround)
	, m_bombSprite(playGround.GetAtlas(), texId)
	, m_pAtlas(playGround.GetAtlas().get()) {

	m_bombs.reserve(s_MaxNrOfBombs);

	m_blastAnimator.SetSpriteIdPattern({0, 1, 2});
	m_blastAnimator.AddAnimOffset(0);
	m_blastAnimator.AddAnimOffset(3);
	m_blastAnimator.AddAnimOffset(6);
	m_blastAnimator.AddAnimOffset(9);
	m_blastAnimator.AddAnimOffset(12);
}

void BombLogic::PlaceBomb(unsigned int tileId) {
	if (m_bombs.size() == s_MaxNrOfBombs)
		return;

	m_bombs.emplace_back(static_cast<unsigned short>(0), static_cast<unsigned short>(tileId));
	auto& tile = m_playGround.GetTileAt(tileId);
	tile.SetFlag(TileEntry::Flags::OccupiedByBomb);
}

void BombLogic::Update(float) {
	for (const auto& bE : m_bombs) {
		m_playGround.GetTileAt(bE.tileId).SubscribeForDraw(&m_bombSprite);
	}

	//m_playGround.SubScribeToPreDraw(&m_bombSprite);
	m_playGround.SubScribeToPostDraw(this);
}

bool BombLogic::Draw(int posX, int posY, float deltaTime) {
	auto base = m_blastAnimator.ComputeSpriteId(0, deltaTime);

	posY += 18;

	// Horizontal blast
	m_pAtlas->Draw(posX+64, posY, base + m_blastAnimator.GetAnimOffset(s_HorizontalEnd));
	m_pAtlas->Draw(posX+128, posY, base + m_blastAnimator.GetAnimOffset(s_Horizontal));
	m_pAtlas->Draw(posX+192, posY, base + m_blastAnimator.GetAnimOffset(s_Middle));
	m_pAtlas->Draw(posX+256, posY, base + m_blastAnimator.GetAnimOffset(s_Horizontal), 180.0);
	m_pAtlas->Draw(posX+320, posY, base + m_blastAnimator.GetAnimOffset(s_HorizontalEnd), 180.0);

	// Vertical blast
	m_pAtlas->Draw(posX+256, posY, base + m_blastAnimator.GetAnimOffset(s_VerticalEnd));
	m_pAtlas->Draw(posX+256, posY+56, base + m_blastAnimator.GetAnimOffset(s_Vertical));
	m_pAtlas->Draw(posX+256, posY+112, base + m_blastAnimator.GetAnimOffset(s_Vertical));
	m_pAtlas->Draw(posX+256, posY+168, base + m_blastAnimator.GetAnimOffset(s_Middle));
	m_pAtlas->Draw(posX+256, posY+224, base + m_blastAnimator.GetAnimOffset(s_Vertical), 180.0);
	m_pAtlas->Draw(posX+256, posY+280, base + m_blastAnimator.GetAnimOffset(s_Vertical), 180.0);
	m_pAtlas->Draw(posX+256, posY+336, base + m_blastAnimator.GetAnimOffset(s_VerticalEnd), 180.0);

	// Horizontal blast core
	m_pAtlas->Draw(posX+64, posY, s_HorizontalEndCore);
	m_pAtlas->Draw(posX+128, posY, s_HorizontalCore);
	m_pAtlas->Draw(posX+192, posY, s_MiddleCore);
	m_pAtlas->Draw(posX+256, posY, s_HorizontalCore, 180.0);
	m_pAtlas->Draw(posX+320, posY, s_HorizontalEndCore, 180.0);
	
	// Vertical blast core
	m_pAtlas->Draw(posX+256, posY, s_VerticalEndCore);
	m_pAtlas->Draw(posX+256, posY+56, s_VerticalCore);
	m_pAtlas->Draw(posX+256, posY+112, s_VerticalCore);
	m_pAtlas->Draw(posX+256, posY+168, s_MiddleCore);
	m_pAtlas->Draw(posX+256, posY+224, s_VerticalCore, 180.0);
	m_pAtlas->Draw(posX+256, posY+280, s_VerticalCore, 180.0);
	m_pAtlas->Draw(posX+256, posY+336, s_VerticalEndCore, 180.0);

	return true;
}

