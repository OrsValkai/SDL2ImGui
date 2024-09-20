// Copyright(c) 2024 Valkai-Németh Béla-Örs

#ifndef SDL_WRAPPER_H
#define SDL_WRAPPER_H

#include <SDL.h>
#include <SDL_image.h>
#include "WrapperHelpers.hpp"

using SDL_TextureUniquePtr = std::unique_ptr<SDL_Texture, constant_t<decltype(SDL_DestroyTexture)*, SDL_DestroyTexture>>;

inline auto SDL_MakeTexturePtr(SDL_Renderer* pRenderer, const char* pName) {
    return make_resource<SDL_TextureUniquePtr>(IMG_LoadTexture, pRenderer, pName);
}

inline auto SDL_MakeTexturePtr(SDL_Renderer* pRenderer, Uint32 format, int access, int w, int h) {
    return make_resource<SDL_TextureUniquePtr>(SDL_CreateTexture, pRenderer, format, access, w, h);
}

inline auto SDL_MakeTexturePtr(SDL_Renderer* pRenderer, SDL_Surface* pSurface) {
    return make_resource<SDL_TextureUniquePtr>(SDL_CreateTextureFromSurface, pRenderer, pSurface);
}

using SDL_SurfaceUniquePtr = std::unique_ptr<SDL_Surface, constant_t<decltype(SDL_FreeSurface)*, SDL_FreeSurface>>;

inline auto SDL_MakeSurfacePtr(int width, int height, int depth, Uint32 format) {
    return make_resource<SDL_SurfaceUniquePtr>(SDL_CreateRGBSurfaceWithFormat, 0, width, height, depth, format);
}

#endif //SDL_WRAPPER_H