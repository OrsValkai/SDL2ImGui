// Copyright(c) 2024 Valkai-N�meth B�la-�rs

#include "TileEntry.hpp"

void TileEntry::SubscribeForDraw(vo::IDrawable* _pDrawable) {
	if (nullptr == pDrawable)
		pDrawable = _pDrawable;
	else {
		_pDrawable->m_pNextDrawable = pDrawable;
		pDrawable = _pDrawable;
	}
}