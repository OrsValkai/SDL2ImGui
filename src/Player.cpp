#include "Player.hpp"

Player::Player(const std::shared_ptr<vo::TextureAtlasBase> textureAtlas)
	: vo::AnimatedSprite(textureAtlas, 20) {

	SetSpriteIdPattern({ 0, 1, 2, 3, 16, 17, 18, 19, 32, 33, 34, 35, 48, 49, 50, 51, 64, 65, 66, 67 });

	// Idle anims
	AddAnimOffset(0);
	AddAnimOffset(4);
	AddAnimOffset(8);
	AddAnimOffset(12);

	// Walk anims
	AddAnimOffset(80);
	AddAnimOffset(84);
	AddAnimOffset(88);
	AddAnimOffset(92);
}

void Player::SetControl(std::shared_ptr<BaseControl> upCtrl) {
	m_pCtrl = upCtrl;
}

void Player::SetTintColor(Uint8 r, Uint8 g, Uint8 b) {
	m_tintR = r;
	m_tintG = g;
	m_tintB = b;
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
			auto tmp = (unsigned char) m_animId;
			tmp -= (unsigned char)AnimId::WalkBack;
			m_animId = (AnimId)tmp;
		}
	}

	return GetTextureAtlas()->DrawTint(posX, posY+16, ComputeSpriteId(static_cast<unsigned char>(m_animId), deltaTime), m_tintR, m_tintG, m_tintB);
}