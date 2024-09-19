#include "SpriteAnimator.hpp"


template <typename T>
SpriteAnimator<T>::SpriteAnimator(const int targetFPS) : m_targetFPS(targetFPS) {
}

template <typename T>
void SpriteAnimator<T>::AppendSpriteIds(std::vector<T>&& toAppend) {
	m_SpriteIds.emplace_back(std::move(toAppend));
}

template <typename T>
bool SpriteAnimator<T>::AppendSpriteIdsAsOffsetFromPrevious(const unsigned char offset) {
	if (m_SpriteIds.empty())
		return false;

	m_SpriteIds.push_back(m_SpriteIds.back());
	for (auto& spriteId : m_SpriteIds.back()) {
		spriteId += offset;
	}

	return true;
}

template <typename T>
int SpriteAnimator<T>::ComputeSpriteId(unsigned char animId, float deltaTime) {
	float targetAcc = 1000.f / static_cast<float>(m_targetFPS);
	m_accTime += deltaTime;

	if (animId != m_lastAnimId) {
		m_lastAnimId = animId;
		m_curSpriteId = 0;
	}

	if (animId < m_SpriteIds.size() && !m_SpriteIds.empty()) {
		if (m_accTime >= targetAcc) {
			m_accTime = fmodf(m_accTime, targetAcc);
			m_curSpriteId++;
		}

		if (m_curSpriteId >= m_SpriteIds[animId].size())
			m_curSpriteId = 0;

		return static_cast<int>(m_SpriteIds[animId][m_curSpriteId]);
	}

	return -1;
}

template class SpriteAnimator<unsigned short>;
template class SpriteAnimator<unsigned char>;

