/*
PivoGUI
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

#include "PIVO_TextureSys.hpp"
#include "PIVO_Math.hpp"
#include "PIVO_SDL.cpp"

#include <iostream>
#include <cinttypes>

namespace pivo{
// === Image ===

std::string Image::getPath() const { return _path; }
void Image::setPath(const std::string& path){ _path = path; }

Image::Image(const std::string& path){ _path = path; }
Image::Image(){}

Image::~Image(){
    SDL_DestroyTexture(_sdltexture);
    _sdltexture = nullptr;
}

// === Texture_Manager ===

void Texture_Manager::_init(SDL_Renderer* renderer) {
    _renderer = renderer;
}

SDL_Texture* const Texture_Manager::getSDLTexture(const Image& img){
    return img._sdltexture;
}

bool Texture_Manager::load(Image& img) {
    if(img._sdltexture!=nullptr){
        img._refCount++;
        return true;
    }

    SDL_Surface* surface = IMG_Load(img._path.c_str());
    if (!surface) {
        std::cerr << "IMG_Load error: " << SDL_GetError() << "\n";
        return false;
    }

    img._sdltexture = SDL_CreateTextureFromSurface(_renderer, surface);
    SDL_DestroySurface(surface);
    if(!img._sdltexture){
        std::cerr << "Texture creation error: " << SDL_GetError() << "\n";
        return false;
    }

    img._refCount=1;

    return true;
}

bool Texture_Manager::unload(Image& img) {
    if (img._sdltexture==nullptr) return true;

    if (--img._refCount <= 0) {
        SDL_DestroyTexture(img._sdltexture);
        img._sdltexture = nullptr;
    }
    
    return true;
}
}