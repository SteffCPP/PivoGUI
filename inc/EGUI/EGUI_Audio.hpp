#pragma once

#include <string>
#include <cinttypes>

struct MIX_Track;
struct MIX_Mixer;

namespace egui{
    struct Audio{
    public:
        enum class State {
            STOPPED,
            PLAYING,
            PAUSED
        };
        void play();
        void pause();
        void stop(const std::uint16_t nFadeOutFrames=0);
        void resume();

        std::string getPath() const { return _path; }

        State getState() const { return _state; }
        bool isPaused() const { return _state == State::PAUSED; }
        bool isPlaying() const { return _state == State::PLAYING; }

        Audio(const std::string& path) : _path(path) {}
    private:
        MIX_Track* _track{nullptr};

        float _volume{1.0f};
        std::size_t _startTime{0};
	    std::size_t _pauseTime{0};
        float _speed{1.0f};
        std::string _path{""};
        State _state{State::STOPPED};

        friend class Audio_System;
    };

    class Audio_System{
    public:
        void play(Audio& audio);
        void pause(Audio& audio);
        void stop(Audio& audio, const unsigned int nFadeOutFrames=0);
        void resume(Audio& audio);

        std::size_t getTime(Audio& audio);
        void setTime(Audio& audio, const std::size_t ms);

        float getVolume(Audio& audio);
        void setVolume(Audio& audio, float volume);
        void increaseVolume(Audio& audio, const int volumeDelta);

        float getSpeed(Audio& audio);
        void setSpeed(Audio& audio, const float speed);

        Audio_System();
    private:
        #define CHECK_TRACK_EXISTS_AND_CREATE if(!audio._track){ \
            if(audio._track = MIX_CreateTrack(_mixmixer); !audio._track) \
                std::cerr << "Error while creating track: " << SDL_GetError() << "\n"; \
            if(MIX_Audio* music = MIX_LoadAudio(_mixmixer, audio._path.c_str(), true); !MIX_SetTrackAudio(audio._track, music)) \
                std::cerr << "Error while setting track audio: " << SDL_GetError() << "\n"; \
        }
        #define CHECK_TRACK_EXISTS(returnValue) if(audio._track == nullptr) return returnValue;
        std::size_t _globalTime{0};
        MIX_Mixer* _mixmixer{nullptr};

        friend class Window;
    };

    extern Audio_System defAudioSys;
} 
