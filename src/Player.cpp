#include "Player.hpp"

Player::Player(SDL_Renderer* pRenderer, const char* pFilePath, unsigned width, unsigned height, unsigned nrSprites) :
	m_sprite(pRenderer, pFilePath, width, height, nrSprites) {

}

bool Player::Draw(float posX, float posY, float deltaTime) {
	return m_sprite.Draw(posX, posY, AnimId::IdleLeft, deltaTime);
}