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

#pragma once

#include <unordered_map>
#include <string>

struct SDL_Renderer;
struct SDL_Texture;

namespace pivo{
class Texture_Manager {
public:
    /// Loads a texture from file or returns cached version if already loaded.
    /// @param path Path of the image file.
    /// @return SDL_Texture pointer (cached).
    static SDL_Texture* load(const std::string& path);

    /// Removes a texture from cache and destroys it.
    /// @param path Path of the texture to remove.
    static void unload(const std::string& path);

    /// Clears all cached textures.
    static void clear();

    /// Checks if a texture is already cached.
    /// @param path Texture path.
    /// @return True if texture exists in cache.
    static bool exists(const std::string& path);

private:
    /// Initializes the texture system.
    static void _init(SDL_Renderer* renderer);

    static inline SDL_Renderer* _renderer{nullptr};

    static inline std::unordered_map<std::string, SDL_Texture*> _cache{};
    static inline std::unordered_map<std::string, int> _refCount{};

    friend class Window;
};
}