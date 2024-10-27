// Copyright(c) 2024 Valkai-N�meth B�la-�rs

#include "AIControl.hpp"
#include <random>
#include <array>

AIControl::AIControl(PlayGround& playGround, unsigned short startTileId)
    : BaseControl(playGround, startTileId) {
}



void AIControl::Update(float deltaTime, vo::IDrawable* pDrawable) {
	static std::default_random_engine randEng;

	if (auto& targetTileId = GetTargetId(); GetCurrentId() == targetTileId) {
		std::array<unsigned short, 4> neighbs;
		auto nCount = m_playGround.GetNeighborIdsForTileAt(neighbs, targetTileId);
        std::uniform_int_distribution<unsigned short> randDist(0, 6);

		for (unsigned short i = 0; i < nCount; i++) {
			if (neighbs[i] != m_prevId) {
				const auto& nTile = m_playGround.GetTileAt(neighbs[i]);

				if ((nTile.HasFlagAny(TileEntry::Flags::Destroyable) || !nTile.HasFlagAny(TileEntry::Flags::Occupied)) && randDist(randEng) >= 3) {
					targetTileId = neighbs[i];
					m_prevId = targetTileId;
					break;
				}
			}
		}
    }

    BaseControl::Update(deltaTime, pDrawable);
}
