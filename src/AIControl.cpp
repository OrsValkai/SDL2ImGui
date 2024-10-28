// Copyright(c) 2024 Valkai-Németh Béla-Örs

#include "AIControl.hpp"
#include <random>
#include <array>

AIControl::AIControl(PlayGround& playGround, unsigned short startTileId)
    : BaseControl(playGround, startTileId) {
}



void AIControl::Update(float deltaTime, vo::IDrawable* pDrawable) {
	static std::default_random_engine randEng;

	if (const auto& targetTileId = GetTargetId(); GetPotentialTargetId() != targetTileId) {
		std::array<unsigned short, 4> neighbs;
		auto nCount = m_playGround.GetNeighborIdsForTileAt(neighbs, targetTileId);
        std::uniform_int_distribution<unsigned short> randDist(0, 6);

		for (unsigned short i = 0; i < nCount; i++) {
			if (neighbs[i] == m_prevId)
				continue;

			const auto& nTile = m_playGround.GetTileAt(neighbs[i]);
			if ((nTile.HasFlagAny(TileEntry::Flags::Destroyable) || !nTile.HasFlagAny(TileEntry::Flags::Occupied)) && randDist(randEng) >= 3) {
				GetPotentialTargetId() = neighbs[i];
				m_prevId = neighbs[i];
				break;
			}
		}
    }

    BaseControl::Update(deltaTime, pDrawable);
}
