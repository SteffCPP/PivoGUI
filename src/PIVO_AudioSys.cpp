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

#include "PIVO_AudioSys.hpp"
#include "PIVO_SDL.cpp"
#include "PIVO_Math.hpp"

#include <iostream>


namespace pivo {
// === Audio ===

Audio::Audio(const std::string& path)
    : _path(path) {}
std::string Audio::getPath() const {
    return _path;
}
Audio::State Audio::getState() const {
    return _state;
}
bool Audio::isPaused() const {
    return _state == State::PAUSED;
}
bool Audio::isPlaying() const {
    return _state == State::PLAYING;
}
void Audio::play(){
    Audio_Manager::play(*this);
}
void Audio::pause(){
    Audio_Manager::pause(*this);
}
void Audio::resume(){
    Audio_Manager::resume(*this);
}
void Audio::stop(std::uint32_t fadeOutFrames){
    Audio_Manager::stop(*this, fadeOutFrames);
}

// === Audio_Manager ===

void Audio_Manager::_init(){
    if (!MIX_Init()) {
        std::cerr << "Failed to init SDL_mixer: " << SDL_GetError() << "\n";
        std::abort();
    }

    _mixmixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);

    if (!_mixmixer) {
        std::cerr << "Failed to create mixer: " << SDL_GetError() << "\n";
    }

    _globalTime = 0;
}
void Audio_Manager::_update(const size_t deltaT){
    _globalTime += deltaT;
}

bool Audio_Manager::load(Audio& audio){
    if(auto it=_cache.find(audio._id); it!=_cache.end()){
        return false;
    }

    std::uint32_t randID = math::generateRandNum<std::uint32_t>(1, 0x90000000);
    auto it=_cache.find(audio._id);
    while(it!=_cache.end()){
        randID = math::generateRandNum<std::uint32_t>(1, 0x90000000);
        it=_cache.find(audio._id);
    }

    audio._id = randID;
    audio._mixtrack = MIX_CreateTrack(_mixmixer);
    if(!audio._mixtrack){
        std::cerr << "Error while creating track: " << SDL_GetError() << "\n";
        return false;
    }

    _cache.emplace(audio._id, audio);

    return true;
}

bool Audio_Manager::unload(Audio& audio){
    auto it=_cache.find(audio._id);
    if(it==_cache.end()) return false;

    MIX_DestroyTrack(audio._mixtrack);
    _cache.erase(it);
    audio._id = 0;
    audio._mixtrack = nullptr;

    return true;
}


void Audio_Manager::clear(){
    for(auto& [_, audio] : _cache){
        MIX_DestroyTrack(audio._mixtrack);
        audio._mixtrack = nullptr;
        audio._id = 0;
    }
    _cache.clear();
}

bool Audio_Manager::exists(const Audio& audio){
    return _cache.contains(audio._id);
}

void Audio_Manager::play(Audio& audio) {
    if(!exists(audio)) load(audio);

    MIX_SetTrackGain(audio._mixtrack, audio._volume);
    MIX_PlayTrack(audio._mixtrack, 0);

    audio._startTime = _globalTime;
    audio._state = Audio::State::PLAYING;
}
void Audio_Manager::pause(Audio& audio) {
    if(!exists(audio)) return;
    if(!MIX_TrackPlaying(audio._mixtrack)) return;

    MIX_PauseTrack(audio._mixtrack);

    audio._pauseTime = _globalTime;
    audio._state = Audio::State::PAUSED;
}
void Audio_Manager::resume(Audio& audio) {
    if(!exists(audio)) return;
    if(!MIX_TrackPaused(audio._mixtrack)) return;

    MIX_ResumeTrack(audio._mixtrack);

    audio._pauseTime = 0;
    audio._state = Audio::State::PLAYING;
}
void Audio_Manager::stop(Audio& audio, std::uint32_t fadeOutFrames) {
    if(!exists(audio)) return;

    if (MIX_TrackPlaying(audio._mixtrack)) {
        MIX_StopTrack(audio._mixtrack, fadeOutFrames);
    }
    
    audio._startTime = 0;
    audio._pauseTime = 0;
    audio._state = Audio::State::STOPPED;
}

std::size_t Audio_Manager::getTime(Audio& audio) {
    if(!exists(audio)) return 0;

    if (audio._state == Audio::State::PLAYING)
        return _globalTime - audio._startTime;

    if (audio._state == Audio::State::PAUSED)
        return audio._pauseTime - audio._startTime;

    return 0;
}

void Audio_Manager::setTime(Audio& audio, std::size_t ms) {
    if(!exists(audio)) return;

    SDL_PropertiesID props = SDL_CreateProperties();
    SDL_SetNumberProperty(props, MIX_PROP_PLAY_START_MILLISECOND_NUMBER, ms);

    MIX_PlayTrack(audio._mixtrack, props);
    SDL_DestroyProperties(props);

    audio._startTime = _globalTime - ms;
}

float Audio_Manager::getVolume(const Audio& audio) {
    return audio._volume;
}
void Audio_Manager::setVolume(Audio& audio, float volume) {
    if (volume < 0.0f) volume = 0.0f;
    if (volume > 1.0f) volume = 1.0f;

    audio._volume = volume;

    if (audio._mixtrack)
        MIX_SetTrackGain(audio._mixtrack, volume);
}
void Audio_Manager::changeVolume(Audio& audio, float delta) {
    setVolume(audio, audio._volume + delta);
}
float Audio_Manager::getSpeed(const Audio& audio) {
    return audio._speed;
}
void Audio_Manager::setSpeed(Audio& audio, float speed) {
    audio._speed = speed;
}
}