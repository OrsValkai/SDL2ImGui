// Copyright(c) 2024 Valkai-Németh Béla-Örs

#include "BombLogic.hpp"

BombLogic::BombSharedSprite::BombSharedSprite(const std::shared_ptr<vo::TextureAtlasBase> textureAtlas, const unsigned texId)
	: m_textureAtlas(textureAtlas)
	, m_fuseAnimator(20)
	, m_texId(texId) {

	m_fuseAnimator.SetSpriteIdPattern({ 0, 1, 2, 3, 4 });
	m_fuseAnimator.AddAnimOffset(16);
}

void BombLogic::BombSharedSprite::Update(float deltaTime) {
	m_fuseAnimator.ComputeSpriteId(0, deltaTime);
}

bool BombLogic::BombSharedSprite::Draw(int posX, int posY) {
	posY += 32;
	
	auto retVal = m_textureAtlas->Draw(posX, posY, m_texId);
	m_textureAtlas->Draw(posX-24, posY-20, m_fuseAnimator.ComputeSpriteId(0, 0.f));

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

	m_bombs.emplace_back(m_bombSprite, static_cast<unsigned short>(tileId));
	
	auto& bE = m_bombs.back();
	auto& tile = m_playGround.GetTileAt(bE.tileId);
	tile.SetFlag(TileEntry::Flags::OccupiedByBomb);

	bE.posX = tile.posX;
	bE.posY = tile.posY;
	bE.tileId -= m_playGround.GetWidth();
	if (bE.tileId >= m_playGround.GetNrOfTiles())
		bE.tileId = 0;
}

void BombLogic::Update(float deltaTime) {
	m_bombSprite.Update(deltaTime);
	for (auto& bE : m_bombs) {
		m_playGround.GetTileAt(bE.tileId).SubscribeForDraw(&bE, 0);
	}

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

