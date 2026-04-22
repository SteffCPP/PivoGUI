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
#include <cinttypes>

struct SDL_Renderer;
struct SDL_Texture;

namespace pivo{
class Image {
public:
    /// Gets the file path of the image.
    /// @return Path string of the image file.
    std::string getPath() const;

    /// Sets the file path of the image.
    /// @param path New image file path.
    void setPath(const std::string& path);

    /// Constructs an Image with a given file path.
    /// @param path Path to the image file.
    Image(const std::string& path);

    /// Default constructor.
    /// Creates an empty Image with no path assigned.
    Image();
private:
    std::string _path{""};
    std::uint32_t _id{0};
    SDL_Texture* _sdltexture{nullptr};

    friend class Texture_Manager;
};

/*class Animation{

};*/

class Texture_Manager {
public:
    /// Loads a texture from file or returns cached version if already loaded.
    /// @param path Path of the image file.
    /// @return SDL_Texture pointer (cached).
    static bool load(Image& img);

    /// Removes a texture from cache and destroys it.
    /// @param path Path of the texture to remove.
    static bool unload(Image& img);

    /// Clears all cached textures.
    static void clear();

    /// Checks if a texture is already cached.
    /// @param path Texture path.
    /// @return True if texture exists in cache.
    static bool exists(const Image& img);

    static SDL_Texture* const getSDLTexture(const Image& img);
private:
    /// Initializes the texture system.
    static void _init(SDL_Renderer* renderer);

    static inline SDL_Renderer* _renderer{nullptr};

    //                                     ID,   Audio Object
    static inline std::unordered_map<std::uint32_t, Image> _cache{};
    //                                     ID,    References Nunmber
    static inline std::unordered_map<std::uint32_t, std::uint32_t> _refCount{};

    friend class Window;
};
}