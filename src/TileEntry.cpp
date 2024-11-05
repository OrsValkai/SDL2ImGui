// Copyright(c) 2024 Valkai-Németh Béla-Örs

#include "TileEntry.hpp"

void TileEntry::SubscribeForDraw(vo::IDrawable* _pDrawable, unsigned int layerId) {
	if (nullptr == pDrawable) {
		_pDrawable->m_layerId = layerId;

		pDrawable = _pDrawable;
	}
	else if (layerId <= pDrawable->m_layerId) {
		_pDrawable->m_pNextDrawable = pDrawable;
		_pDrawable->m_layerId = layerId;

		pDrawable = _pDrawable;
	}
	else {
		auto pNextDrawable = pDrawable;
		while (nullptr != pNextDrawable) {
			if (layerId > pNextDrawable->m_layerId) {
				_pDrawable->m_pNextDrawable = pNextDrawable->m_pNextDrawable;
				_pDrawable->m_layerId = layerId;

				pNextDrawable->m_pNextDrawable = _pDrawable;
				break;
			}

			pNextDrawable = pNextDrawable->m_pNextDrawable;
		}
	}
}