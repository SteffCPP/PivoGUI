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
struct Audio {
public:
    enum class State {
        STOPPED,
        PLAYING,
        PAUSED
    };

    Audio(const std::string& path);

    void play();
    void pause();
    void resume();
    void stop(std::uint32_t fadeOutFrames=0);

    std::string getPath() const;

    State getState() const;
    bool isPaused() const;
    bool isPlaying() const;

private:
    MIX_Track* _track{nullptr};

    float _volume{1.0f};
    std::size_t _startTime{0};
    std::size_t _pauseTime{0};
    float _speed{1.0f};
    std::string _path;
    State _state{State::STOPPED};

    friend class Audio_Manager;
};

class Audio_Manager {
public:
    static void play(Audio& audio);
    static void pause(Audio& audio);
    static void resume(Audio& audio);
    static void stop(Audio& audio, std::uint32_t fadeOutFrames = 0);

    static std::size_t getTime(Audio& audio);
    static void setTime(Audio& audio, std::size_t ms);

    static float getVolume(const Audio& audio);
    static void setVolume(Audio& audio, float volume);
    static void increaseVolume(Audio& audio, float delta);

    static float getSpeed(const Audio& audio);
    static void setSpeed(Audio& audio, float speed);

private:
    static void _init();
    static void _update(const size_t deltaT);
    static inline MIX_Mixer* _mixmixer{nullptr};
    static inline std::size_t _globalTime{0};

    friend class Window;
};
}
