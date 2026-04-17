#include "EGUI_Audio.hpp"
#include "EGUI_SDL.cpp"

#include <iostream>
namespace egui{
    Audio_System defAudioSys;

Audio_System::Audio_System(){
    if(!MIX_Init()){ \
        std::cerr << "Couldn't initialize SDL3_mixer " << SDL_GetError() << "\n"; 
        abort(); 
    }

    _mixmixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);

    if(!_mixmixer){
        std::cerr << "Couldn't initialize defAudioSys: " << SDL_GetError() << "\n";
        return;
    }
}

void Audio_System::play(Audio audio){
    CHECK_AUDIO_EXISTS
    MIX_PlayTrack(audio._track, 0);

    audio._startTime=_globalPlayTime;
}
void Audio_System::pause(Audio audio){
    CHECK_AUDIO_EXISTS
    MIX_PauseTrack(audio._track);

    audio._pauseTime = _globalPlayTime;
}
void Audio_System::resume(Audio audio){
    CHECK_AUDIO_EXISTS
    MIX_ResumeTrack(audio._track);

    audio._pauseTime=0;
}
void Audio_System::stop(Audio audio, const unsigned int nFadeOutFrames){
    CHECK_AUDIO_EXISTS
    MIX_StopTrack(audio._track, nFadeOutFrames);

    MIX_DestroyTrack(audio._track);
    audio._startTime=0;
}

std::size_t Audio_System::getTime(Audio audio){
    #define RETURN_CHECK if(audio._startTime > audio._pauseTime){ \
            return _globalPlayTime - audio._startTime; \
        }else{  \
            return _globalPlayTime - audio._pauseTime; }
        
    if(_globalPlayTime>audio._startTime){
        RETURN_CHECK
    }
    else{
        RETURN_CHECK
    }
}
void Audio_System::setTime(Audio audio, const double time){}

void Audio_System::getVolume(Audio audio){}
void Audio_System::setVolume(Audio audio, const unsigned int volume){}
void Audio_System::increaseVolume(Audio audio, const int volumeDelta){}

void Audio_System::getSpeed(Audio audio){}
void Audio_System::setSpeed(Audio audio, const float speed){}
}