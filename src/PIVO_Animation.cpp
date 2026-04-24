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

#include "PIVO/PIVO_Animation.hpp"
#include "PIVO_SDL.cpp"

namespace pivo{
SpriteAnimation::SpriteAnimation(SpriteAnimation&& other) : 
    _frames(std::move(other._frames)),
    _frameDuration(other._frameDuration),
    _time(other._time),
    _currentFrame(other._currentFrame),
    _path(other._path),
    _speed(other._speed),
    _playing(other._playing),
    _loop(other._loop)
{
    other._frames.clear();
}

SpriteAnimation::SpriteAnimation(std::vector<Texture*> textures,
                                 float frameDuration,
                                 bool loop)
    : _frames(std::move(textures)),
      _frameDuration(frameDuration),
      _loop(loop),
      _currentFrame(0),
      _time(0.0f),
      _playing(false),
      _speed(1.0f)
{
}
SpriteAnimation::~SpriteAnimation(){
    _frames.clear();
}

void SpriteAnimation::addFrame(Texture* texture){
    if(texture)
        _frames.push_back(texture);
}

void SpriteAnimation::update(float delta){
    if(!_playing || _frames.empty()) return;

    _time += delta * _speed;

    while(_time >= _frameDuration){
        _time -= _frameDuration;
        _currentFrame++;

        if(_currentFrame >= _frames.size()){
            if(_loop){
                _currentFrame = 0;
            } else {
                _currentFrame = _frames.size() - 1;
                _playing = false;
                break;
            }
        }
    }
}

void SpriteAnimation::play(){ _playing = true; }
void SpriteAnimation::pause(){ _playing = false; }
void SpriteAnimation::stop(){ 
    _playing = false; 
    _currentFrame = 0; 
    _time = 0.0f; 
}
void SpriteAnimation::reset(){
    _currentFrame = 0;
    _time = 0.0f;
}

Texture* SpriteAnimation::getCurrentFrame() const{
    if(_frames.empty()) return nullptr;
    return _frames[_currentFrame];
}

void SpriteAnimation::toggleLoop(const bool loop){ _loop = loop; }
void SpriteAnimation::setSpeed(const float speed){ _speed = (speed < 0.0f) ? 0.0f : speed; }
bool SpriteAnimation::isPlaying() const { return _playing; }
}