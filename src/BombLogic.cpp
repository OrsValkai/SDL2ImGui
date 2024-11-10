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

	BombEntry::s_pSharedSprite = &m_bombSprite;

	m_blastAnimator.SetSpriteIdPattern({0, 1, 2});
	m_blastAnimator.AddAnimOffset(0);
	m_blastAnimator.AddAnimOffset(3);
	m_blastAnimator.AddAnimOffset(6);
	m_blastAnimator.AddAnimOffset(9);
	m_blastAnimator.AddAnimOffset(12);

	for (auto& bE : m_blasts) {
		bE.reserve((s_MaxBlastLength*4*2)+2);
	}
}

void BombLogic::PlaceBomb(unsigned int tileId) {
	for(auto& bE : m_bombs) {
		if (bE.counterSec < 0.f) {
			bE.tileId = static_cast<unsigned short>(tileId);
			auto& tile = m_playGround.GetTileAt(bE.tileId);
			tile.SetFlag(TileEntry::Flags::OccupiedByBomb);

			bE.counterSec = s_BlastTimeSec + 5000.f;

			bE.posX = tile.posX;
			bE.posY = tile.posY;
			bE.drawTileId = bE.tileId - m_playGround.GetWidth();
			if (bE.drawTileId >= m_playGround.GetNrOfTiles())
				bE.drawTileId = 0;

			break;
		}
	}
}

void BombLogic::CreateBlast(BombEntry& bE, std::vector<BlastEntry>& blast) {
	auto& cTile = m_playGround.GetTileAt(bE.tileId);
	cTile.ClearFlag(TileEntry::Flags::OccupiedByBomb);

	// Center
	cTile.SetFlag(TileEntry::Flags::HasBlast);
	blast.emplace_back(bE.tileId, bE.posX, (signed short)(bE.posY + 18), s_Middle, 0);

	// Branch out in the 4 directions while possible
	std::array<vo::Vector2D<signed short>, 4> dirs{{{-1,0}, {1,0}, {0,-1}, {0,1}}};
	std::array<BlastDrawHelper, 4> drawMid{{{s_Horizontal, 0}, {s_Horizontal, 180}, {s_Vertical, 0}, {s_Vertical, 180}}};
	std::array<BlastDrawHelper, 4> drawEnd{{{s_HorizontalEnd, 0}, {s_HorizontalEnd, 180}, {s_VerticalEnd, 0}, {s_VerticalEnd, 180}}};
	for (int i = 0; i < 4; i++) {
		auto prevTileId = bE.tileId;
		for (int j = 0; j < m_blastLen; j++) {
			auto tileId = m_playGround.GetNeighborIdForTileAt(dirs[i], prevTileId);
			if (tileId >= m_playGround.GetNrOfTiles())
				break;

			auto& tile = m_playGround.GetTileAt(tileId);
			bool hasTile = tile.HasFlagAll(TileEntry::Flags::OccupiedByTile);

			// Break here in case it's not a destroyable tile
			if (hasTile && !tile.HasFlagAll(TileEntry::Flags::Destroyable))
				break;

			prevTileId = tileId;
			tile.ClearFlag(TileEntry::Flags::OccupiedByTile);
			tile.SetFlag(TileEntry::Flags::HasBlast);

			if (j >= 1) {
				blast.back().typeId = drawMid[i].typeId;
			}

			blast.emplace_back(tileId, tile.posX, (signed short)(tile.posY + 18), drawEnd[i].typeId, drawEnd[i].angle);

			// We only go 1 deep, so break after
			if (hasTile)
				break;
		}
	}
}

void BombLogic::Update(float deltaTime) {
	m_bombSprite.Update(deltaTime);

	for (int i = 0; i < m_bombs.size(); i++) {
		auto& bE = m_bombs[i];
		bE.counterSec -= deltaTime;

		if (bE.tileId < m_playGround.GetNrOfTiles() && m_playGround.GetTileAt(bE.tileId).HasFlagAny(TileEntry::Flags::HasBlast)) {
			bE.counterSec = s_BlastTimeSec-0.0001f;
		}
		
		if (bE.counterSec < s_BlastTimeSec) {
			if (constexpr auto tileMax = std::numeric_limits<unsigned short>::max(); bE.tileId != tileMax) {
				// Create blast here
				CreateBlast(bE, m_blasts[i]);

				bE.tileId = tileMax;
			}
			else if (bE.counterSec <= 0.f) {
				// Clear blast here
				for (const auto& blast : m_blasts[i]) {
					m_playGround.GetTileAt(blast.tileId).ClearFlag(TileEntry::Flags::HasBlast);
				}
				m_blasts[i].clear();
				bE.counterSec = -1.f;
			}
		}
		else {
			m_playGround.GetTileAt(bE.drawTileId).SubscribeForDraw(&bE, 0);
		}
	}

	m_playGround.SubScribeToPostDraw(this);
}

bool BombLogic::Draw(int posX, int posY, float deltaTime) {
	auto base = m_blastAnimator.ComputeSpriteId(0, deltaTime);
	for (const auto& bEA : m_blasts) {
		for (const auto& bE : bEA) {
			m_pAtlas->Draw(bE.posX, bE.posY, base + m_blastAnimator.GetAnimOffset(bE.typeId), bE.angle);
		}
	}

	for (const auto& bEA : m_blasts) {
		for (const auto& bE : bEA) {
			m_pAtlas->Draw(bE.posX, bE.posY, s_coreIds[bE.typeId], bE.angle);
		}
	}

	//BlastDebugDraw(posX, posY, base);

	return true;
}

void BombLogic::BlastDebugDraw(int posX, int posY, int base)
{
	// Blast debug start
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
	m_pAtlas->Draw(posX+64, posY, s_coreIds[s_HorizontalEnd]);
	m_pAtlas->Draw(posX+128, posY, s_coreIds[s_Horizontal]);
	m_pAtlas->Draw(posX+192, posY, s_coreIds[s_Middle]);
	m_pAtlas->Draw(posX+256, posY, s_coreIds[s_Horizontal], 180.0);
	m_pAtlas->Draw(posX+320, posY, s_coreIds[s_HorizontalEnd], 180.0);

	// Vertical blast core
	m_pAtlas->Draw(posX + 256, posY, s_coreIds[s_VerticalEnd]);
	m_pAtlas->Draw(posX+256, posY+56, s_coreIds[s_Vertical]);
	m_pAtlas->Draw(posX+256, posY+112, s_coreIds[s_Vertical]);
	m_pAtlas->Draw(posX+256, posY+168, s_coreIds[s_Middle]);
	m_pAtlas->Draw(posX+256, posY+224, s_coreIds[s_Vertical], 180.0);
	m_pAtlas->Draw(posX+256, posY+280, s_coreIds[s_Vertical], 180.0);
	m_pAtlas->Draw(posX+256, posY+336, s_coreIds[s_VerticalEnd], 180.0);
}

