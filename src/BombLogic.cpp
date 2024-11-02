// Copyright(c) 2024 Valkai-N�meth B�la-�rs

#include "BombLogic.hpp"

BombSprite::BombSprite(const std::shared_ptr<vo::TextureAtlasBase> textureAtlas, const unsigned texId)
	: Sprite(textureAtlas, texId)
	, m_fuseAnimator(20) {

	m_fuseAnimator.SetSpriteIdPattern({ 0, 1, 2, 3, 4 });
	m_fuseAnimator.AddAnimOffset(16);
}

bool BombSprite::Draw(int posX, int posY, float deltaTime) {
	posY += 32;
	
	auto retVal = vo::Sprite::Draw(posX, posY, deltaTime);
	GetTextureAtlas()->Draw(posX-24, posY-20, m_fuseAnimator.ComputeSpriteId(0, deltaTime));

	return retVal;
}

namespace {
	inline const unsigned char Middle = 2;
	inline const unsigned char Horizontal = 0;
	inline const unsigned char Vertical = 3;
	inline const unsigned char HorizontalEnd = 1;
	inline const unsigned char VerticalEnd= 4;

	inline const unsigned char MiddleCore = 15;
	inline const unsigned char HorizontalCore = 22;
	inline const unsigned char VerticalCore = 21;
	inline const unsigned char HorizontalEndCore = 24;
	inline const unsigned char VerticalEndCore = 23;
}

BombLogic::BombLogic(PlayGround& playGround, const unsigned texId)
	: m_blastAnimator(20)
	
	, m_playGround(playGround)
	, m_bomb(playGround.GetAtlas(), texId)
	, m_pAtlas(playGround.GetAtlas().get()) {

	m_blastAnimator.SetSpriteIdPattern({0, 1, 2});
	m_blastAnimator.AddAnimOffset(0);
	m_blastAnimator.AddAnimOffset(3);
	m_blastAnimator.AddAnimOffset(6);
	m_blastAnimator.AddAnimOffset(9);
	m_blastAnimator.AddAnimOffset(12);
}

void BombLogic::Update(float) {
	m_playGround.SubScribeToPreDraw(&m_bomb);
	m_playGround.SubScribeToPostDraw(this);
}

bool BombLogic::Draw(int posX, int posY, float deltaTime) {
	auto base = m_blastAnimator.ComputeSpriteId(0, deltaTime);

	posY += 18;

	m_pAtlas->Draw(posX+64, posY, base + m_blastAnimator.GetAnimOffset(HorizontalEnd));
	m_pAtlas->Draw(posX+128, posY, base + m_blastAnimator.GetAnimOffset(Horizontal));
	m_pAtlas->Draw(posX+192, posY, base + m_blastAnimator.GetAnimOffset(Middle));
	m_pAtlas->Draw(posX+256, posY, base + m_blastAnimator.GetAnimOffset(VerticalEnd));
	m_pAtlas->Draw(posX+256, posY+56, base + m_blastAnimator.GetAnimOffset(Vertical));
	m_pAtlas->Draw(posX+256, posY+112, base + m_blastAnimator.GetAnimOffset(Vertical));
	m_pAtlas->Draw(posX+256, posY+168, base + m_blastAnimator.GetAnimOffset(Middle));
	m_pAtlas->Draw(posX+256, posY+224, base + m_blastAnimator.GetAnimOffset(Vertical), 180.0);
	m_pAtlas->Draw(posX+256, posY+280, base + m_blastAnimator.GetAnimOffset(Vertical), 180.0);
	m_pAtlas->Draw(posX+256, posY+336, base + m_blastAnimator.GetAnimOffset(VerticalEnd), 180.0);

	m_pAtlas->Draw(posX+64, posY, HorizontalEndCore);
	m_pAtlas->Draw(posX+128, posY, HorizontalCore);
	m_pAtlas->Draw(posX+192, posY, MiddleCore);
	m_pAtlas->Draw(posX+256, posY, VerticalEndCore);
	m_pAtlas->Draw(posX+256, posY+56, VerticalCore);
	m_pAtlas->Draw(posX+256, posY+112, VerticalCore);
	m_pAtlas->Draw(posX+256, posY+168, MiddleCore);
	m_pAtlas->Draw(posX+256, posY+224, VerticalCore, 180.0);
	m_pAtlas->Draw(posX+256, posY+280, VerticalCore, 180.0);
	m_pAtlas->Draw(posX+256, posY+336, VerticalEndCore, 180.0);

	return true;
}

