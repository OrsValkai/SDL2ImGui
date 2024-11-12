// Copyright(c) 2024 Valkai-Németh Béla-Örs

#include "SpriteAnimator.hpp"
#include <SDL_assert.h>

namespace vo {

	template <typename T>
	SpriteAnimator<T>::SpriteAnimator(const int targetFPS) : m_targetFPS(targetFPS) {
	}

	template <typename T>
	void SpriteAnimator<T>::SetSpriteIdPattern(std::vector<T>&& pattern) {
		m_spriteIdPattern = std::move(pattern);
	}

	template <typename T>
	void SpriteAnimator<T>::AddAnimOffset(const T offset) {
		m_animOffset.push_back(offset);
	}

	template <typename T>
	T SpriteAnimator<T>::GetAnimOffset(unsigned char animId) const {
		if (animId < m_animOffset.size())
			return m_animOffset[animId];

		return 0;
	}

	template <typename T>
	int SpriteAnimator<T>::ComputeSpriteId(unsigned char animId, float deltaTime) {
		float targetAcc = 1000.f / static_cast<float>(m_targetFPS);
		m_accTime += deltaTime;

		if (animId != m_lastAnimId) {
			m_lastAnimId = animId;
			m_curPatternId = 0;
		}

		if (animId < m_animOffset.size() && !m_spriteIdPattern.empty()) {
			if (m_accTime >= targetAcc) {
				m_accTime = fmodf(m_accTime, targetAcc);
				m_curPatternId++;
			}

			if (m_curPatternId >= m_spriteIdPattern.size())
				m_curPatternId = 0;

			return static_cast<int>(m_spriteIdPattern[m_curPatternId] + m_animOffset[animId]);
		}

		// Assert the error, on release builds this won't fire
		SDL_assert(!"Missing data for animator, object won't be drawn, make sure you called SetSpriteIdPattern() and AddAnimOffset()!");

		return -1;
	}

	template class SpriteAnimator<unsigned short>;
	template class SpriteAnimator<unsigned char>;

}
