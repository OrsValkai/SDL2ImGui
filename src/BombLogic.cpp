// Copyright(c) 2024 Valkai-Németh Béla-Örs

#include "BombLogic.hpp"

BombLogic::BombLogic(PlayGround& playGround, const unsigned texId)
	: vo::Sprite(playGround.GetAtlas(), texId)
	, m_blastAnimator(20)
	, m_fuseAnimator(20)
	, m_playGround(playGround) {
}

void BombLogic::Update(float deltaTime) {
}

bool BombLogic::Draw(int posX, int posY, float deltaTime) {
	return false;
}
