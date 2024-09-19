#include "AtlassedSpriteBase.hpp"

AtlassedSpriteBase::AtlassedSpriteBase(SDL_Renderer* pRenderer, const char* pFilePath, unsigned nrSprites)
: m_pRenderer(pRenderer), m_nrSprites(nrSprites) {
	m_upTexture = SDL_MakeTexturePtr(m_pRenderer, pFilePath);
}

bool AtlassedSpriteBase::ReadTextureExtents(int& w, int& h) const {
	return (0 == SDL_QueryTexture(m_upTexture.get(), nullptr, nullptr, &w, &h));
}