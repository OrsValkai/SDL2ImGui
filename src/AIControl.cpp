// Copyright(c) 2024 Valkai-Németh Béla-Örs

#include "AIControl.hpp"
#include <random>
#include <array>

AIControl::AIControl(PlayGround& playGround, unsigned short startTileId)
    : BaseControl(playGround, startTileId) {
}



void AIControl::Update(float deltaTime, Player* pParent) {
	static std::default_random_engine randEng;

	if (deltaTime <= 0.001f) {
		BaseControl::Update(deltaTime, pParent);
		return;
	}

	//std::cout << "AI update\n";
	const auto& targetTileId = GetTargetId();
	if (m_shouldPickNewTarget) {
		std::array<unsigned short, 4> neighbs;
		auto nCount = m_playGround.GetNeighborIdsForTileAt(neighbs, targetTileId);
        std::uniform_int_distribution<unsigned short> randDist(0, 6);

		const auto& currentId = GetCurrentId();
		for (unsigned short i = 0; i < nCount; i++) {
			// Favor new target instead of going back to where we came from
			if (neighbs[i] == currentId)
				continue;

			// Check tile is walkable and do the dice roll to randomize direction
			auto& nTile = m_playGround.GetTileAt(neighbs[i]);
			if ((nTile.HasFlagAll(TileEntry::Flags::DestroyableTile) || !nTile.HasFlagAny(TileEntry::Flags::Occupied)) && randDist(randEng) >= 3) {
				m_prevId = neighbs[i];
				GetPotentialTargetId() = m_prevId;
				m_shouldPickNewTarget = false;

				nTile.ClearFlag(TileEntry::Flags::OccupiedByTile);

				//std::cout << "AI new target!\n";
				break;
			}
		}
	// Potential target became actual target, so we should pick a new potential target
	} else if (targetTileId == m_prevId) {
		m_shouldPickNewTarget = true;
	}

    BaseControl::Update(deltaTime, pParent);
}

void AIControl::Reset() {
	BaseControl::Reset();

	m_prevId = std::numeric_limits<unsigned short>::max();
	m_shouldPickNewTarget = true;
}
