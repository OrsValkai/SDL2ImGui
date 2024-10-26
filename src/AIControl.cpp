// Copyright(c) 2024 Valkai-Németh Béla-Örs

#include "AIControl.hpp"

AIControl::AIControl(PlayGround& playGround, unsigned short startTileId)
    : BaseControl(playGround, startTileId) {
}



void AIControl::Update(float deltaTime, vo::IDrawable* pDrawable) {
    

    BaseControl::Update(deltaTime, pDrawable);
}
