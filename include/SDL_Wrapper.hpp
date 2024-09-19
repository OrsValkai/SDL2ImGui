// Copyright(c) 2024 Valkai-Németh Béla-Örs

#ifndef SDL_WRAPPER_H
#define SDL_WRAPPER_H

#include <SDL.h>
#include <SDL_image.h>
#include "WrapperHelpers.hpp"

inline auto SDL_DestroyTextureTester(SDL_Texture* pTexture) {
    return SDL_DestroyTexture(pTexture);
}

using SDL_TextureUniquePtr = std::unique_ptr<SDL_Texture, constant_t<decltype(SDL_DestroyTexture)*, SDL_DestroyTexture>>;

inline auto SDL_MakeTexturePtr(SDL_Renderer* pRenderer, const char* pName) {
    return make_resource<SDL_TextureUniquePtr>(IMG_LoadTexture, pRenderer, pName);
}

#endif //SDL_WRAPPER_H