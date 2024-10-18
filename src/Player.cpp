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
		const auto& dir = m_pCtrl->GetMoveDir();
		
		posX = std::lroundf(pos.x);
		posY = std::lroundf(pos.y);

		if (dir.x > 0) {
			m_animId = AnimId::WalkRight;
		} else if (dir.x < 0) {
			m_animId = AnimId::WalkLeft;
		} else if (dir.y > 0) {
			m_animId = AnimId::WalkFront;
		} else if (dir.y < 0) {
			m_animId = AnimId::WalkBack;
		} else if (m_animId >= AnimId::WalkBack) {
			unsigned char tmp = (unsigned char) m_animId;

			tmp -= (unsigned char)AnimId::WalkBack;
			m_animId = (AnimId)tmp;
		}
	}

	return m_sprite.Draw(posX, posY, m_animId, deltaTime);
}