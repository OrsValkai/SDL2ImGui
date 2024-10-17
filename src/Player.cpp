#include "Player.hpp"

Player::Player(SDL_Renderer* pRenderer, const char* pFilePath, unsigned width, unsigned height, unsigned nrSprites) :
	m_sprite(pRenderer, pFilePath, width, height, nrSprites) {

}

std::shared_ptr<BaseControl> Player::AddControl(std::shared_ptr<BaseControl> upCtrl) {
	m_pCtrl = upCtrl;

	return m_pCtrl;
}

void Player::Update(float deltaTime) {
	if (!m_pCtrl)
		return;

	m_pCtrl->Update(deltaTime, this);
}

bool Player::Draw(int posX, int posY, float deltaTime) {
	if (m_pCtrl) {
		const auto& pos = m_pCtrl->GetPos();
		
		posX = std::lroundf(pos.x);
		posY = std::lroundf(pos.y);
	}

	return m_sprite.Draw(posX, posY, AnimId::IdleLeft, deltaTime);
}