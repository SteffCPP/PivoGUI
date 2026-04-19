/*
EGUI - Embedded Graphics Utility Interface
Copyright (c) 2026 Stefano Rando (randostefano39@proton.me)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required. 
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
*/

#include "EGUI_TextureManager.hpp"
#include "EGUI_SDL.cpp"

#include <iostream>

namespace egui{
void Texture_Manager::_init(SDL_Renderer* renderer) {
    _renderer = renderer;
}

SDL_Texture* Texture_Manager::load(const std::string& path) {
    if (auto it = _cache.find(path); it != _cache.end()) {
        _refCount[path]++;
        return it->second;
    }

    SDL_Surface* surface = IMG_Load(path.c_str());
    if (!surface) {
        std::cerr << "IMG_Load error: " << SDL_GetError() << "\n";
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(_renderer, surface);
    SDL_DestroySurface(surface);

    if (!texture) {
        std::cerr << "Texture creation error: " << SDL_GetError() << "\n";
        return nullptr;
    }

    _cache[path] = texture;
    _refCount[path] = 1;

    return texture;
}

void Texture_Manager::unload(const std::string& path) {
    auto it = _cache.find(path);
    if (it == _cache.end()) return;

    if (--_refCount[path] <= 0) {
        SDL_DestroyTexture(it->second);
        _cache.erase(it);
        _refCount.erase(path);
    }
}

void Texture_Manager::clear() {
    for (auto& [path, tex] : _cache) {
        SDL_DestroyTexture(tex);
    }
    _cache.clear();
    _refCount.clear();
}

bool Texture_Manager::exists(const std::string& path) {
    return _cache.contains(path);
}
}