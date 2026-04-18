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

#include "EGUI_Audio.hpp"
#include "EGUI_SDL.cpp"

#include <iostream>
#include <cinttypes>

namespace egui{
#define CHECK_TRACK_EXISTS_AND_CREATE if(!audio._track){ \
        if(audio._track = MIX_CreateTrack(_mixmixer); !audio._track) \
            std::cerr << "Error while creating track: " << SDL_GetError() << "\n"; \
        if(MIX_Audio* music = MIX_LoadAudio(_mixmixer, audio._path.c_str(), true); !MIX_SetTrackAudio(audio._track, music)) \
            std::cerr << "Error while setting track audio: " << SDL_GetError() << "\n"; \
    }
#define CHECK_TRACK_EXISTS(returnValue) if(audio._track == nullptr) return returnValue;
        

// === Audio ===

void Audio::play(){
    defAudioSys.play(*this);
}
void Audio::stop(const std::uint16_t nFadeOutFrames){
    defAudioSys.stop(*this, nFadeOutFrames);
}
void Audio::resume(){
    defAudioSys.resume(*this);
}
void Audio::pause(){
    defAudioSys.pause(*this);
}
std::string Audio::getPath() const { return _path; }
Audio::State Audio::getState() const { return _state; }
bool Audio::isPaused() const { return _state == State::PAUSED; }
bool Audio::isPlaying() const { return _state == State::PLAYING; }
Audio::Audio(const std::string& path){ _path = path; }

// === Audio_System ===

Audio_System::Audio_System(){
    if(!MIX_Init()){
        std::cerr << "Couldn't initialize SDL3_mixer " << SDL_GetError() << "\n"; 
        abort(); 
    }

    _mixmixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);

    if(!_mixmixer){
        std::cerr << "Couldn't initialize defAudioSys: " << SDL_GetError() << "\n";
        return;
    }

    _globalTime = 0;
}

void Audio_System::play(Audio& audio){
    CHECK_TRACK_EXISTS_AND_CREATE
    MIX_SetTrackGain(audio._track, audio._volume);
    MIX_PlayTrack(audio._track, 0);

    audio._startTime = _globalTime;
    audio._state = Audio::State::PLAYING;
}
void Audio_System::pause(Audio& audio){
    CHECK_TRACK_EXISTS()
    if(!MIX_TrackPlaying(audio._track)) return;
    
    MIX_PauseTrack(audio._track);

    audio._pauseTime = _globalTime;
    audio._state = Audio::State::PAUSED;
}
void Audio_System::resume(Audio& audio){
    CHECK_TRACK_EXISTS()
    if(!MIX_TrackPaused(audio._track)) return;

    MIX_ResumeTrack(audio._track);

    audio._pauseTime=0;
    audio._state = Audio::State::PLAYING;
}
void Audio_System::stop(Audio& audio, const unsigned int nFadeOutFrames){
    CHECK_TRACK_EXISTS()
    if(!MIX_TrackPlaying(audio._track)) return;

    MIX_StopTrack(audio._track, nFadeOutFrames);

    MIX_DestroyTrack(audio._track);
    audio._track = nullptr;
    audio._startTime = 0;
    audio._state = Audio::State::STOPPED;
}

std::size_t Audio_System::getTime(Audio& audio){
    CHECK_TRACK_EXISTS(0);
    if(audio._state == Audio::State::PLAYING){
        return _globalTime - audio._startTime;
    }

    if(audio._state == Audio::State::PAUSED){
        return audio._pauseTime - audio._startTime;
    }
    
    return 0;
}
void Audio_System::setTime(Audio& audio, const std::size_t ms){
    CHECK_TRACK_EXISTS()

    SDL_PropertiesID props = SDL_CreateProperties();
    SDL_SetNumberProperty(props, MIX_PROP_PLAY_START_MILLISECOND_NUMBER, ms);
    MIX_PlayTrack(audio._track, props);

    SDL_DestroyProperties(props);

    if(audio._state == Audio::State::PAUSED){
        MIX_PauseTrack(audio._track);
        audio._pauseTime = _globalTime;
    }else if(audio._state == Audio::State::STOPPED){
        MIX_StopTrack(audio._track, 0);
        audio._pauseTime = 0;
        audio._startTime = 0;
    }else
        audio._pauseTime = 0;

    audio._startTime = _globalTime - ms;
}

float Audio_System::getVolume(Audio& audio){ return audio._volume; }
void Audio_System::setVolume(Audio& audio, float volume){
    if(volume<0.0f) volume = 0.0f;
    if(volume>1.0f) volume = 1.0f;
    audio._volume = volume;

    CHECK_TRACK_EXISTS()

    MIX_SetTrackGain(audio._track, audio._volume);
}
void Audio_System::increaseVolume(Audio& audio, const int volumeDelta){}

float Audio_System::getSpeed(Audio& audio){ return audio._speed; }
void Audio_System::setSpeed(Audio& audio, const float speed){}


    Audio_System defAudioSys;
}