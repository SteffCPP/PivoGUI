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
#include <memory>
#include <vector>

#include "PIVO/Primitives/PIVO_Vector.hpp"
#include "PIVO/Systems/PIVO_TextureSys.hpp"

struct SDL_Texture;
struct SDL_Rect;

namespace pivo{
class SpriteAnimation{
public:
    SpriteAnimation(std::vector<Texture*> textures, float frameDuration=100.0f, bool loop=true);
    SpriteAnimation(SpriteAnimation&& other);
    ~SpriteAnimation();

    void addFrame(Texture* texture);

    void update(float delta);

    void play();
    void pause();
    void stop();
    void reset();

    Texture* getCurrentFrame() const;

    void toggleLoop(const bool loop);
    void setSpeed(const float speed);
    bool isPlaying() const;
private:
    std::vector<Texture*> _frames;

    float _frameDuration{100.0f}; 
    float _time{0.0f};
    std::size_t _currentFrame{0};
    std::string _path{""};
    float _speed{1.0f};

    bool _playing{true};
    bool _loop{true};

    friend class Texture_Manager;
};


}