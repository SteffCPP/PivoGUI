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

        std::string getPath() const;

        State getState() const;
        bool isPaused() const;
        bool isPlaying() const;

        Audio(const std::string& path);
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
        std::size_t _globalTime=0;
        MIX_Mixer* _mixmixer{nullptr};

        friend class Window;
    };

    extern Audio_System defAudioSys;
} 
