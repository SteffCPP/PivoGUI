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

#include <string>
#include <unordered_map>
#include <cinttypes>

struct MIX_Track;
struct MIX_Mixer;
struct MIX_Audio;

namespace pivo{

/// @struct Audio. 
/// @brief Struct that represents an Audio. 
///
/// All the methods that it contains are non other than calls to the Audio_Manager.
struct Audio {
public:

    /// State of an Audio.
    enum class State {
        STOPPED,   ///< The track is currently stopped.
        PLAYING,   ///< The track is currently playing.
        PAUSED     ///< The track is currently paused and can be resumed.
    };

    /// Plays the audio.
    void play();

    /// Pauses the audio.
    /// If the audio is not playing, this function does nothing.
    void pause();

    /// Resumes the audio.
    /// If the audio is not paused, this function does nothing.
    void resume();

    /// Returns the volume of the Audio.
    float getVolume();

    /// Sets the volume of the Audio.
    /// @param volume Volume in range [0.0 - 1.0].
    void setVolume(float volume);

    /// Changes the volume of an Audio.
    /// @param delta Volume delta in range [-1.0 - 1.0].
    void changeVolume(float delta);

    /// Stops the audio.
    /// If the audio is not playing or paused, this function does nothing.
    /// @param fadeOutFrames Number of frames used for fade-out before stopping.
    void stop(std::uint32_t fadeOutFrames = 0);

    /// Gets the file path of the audio.
    /// @return Path string of the audio file.
    std::string getPath() const;

    /// Gets the current state of the audio.
    /// @return Current Audio::State value.
    State getState() const;

    /// Checks if the audio is currently paused.
    /// @return True if paused, false otherwise.
    bool isPaused() const;

    /// Checks if the audio is currently playing.
    /// @return True if playing, false otherwise.
    bool isPlaying() const;

    /// Constructs an Audio instance from a file path.
    /// @param path Path of the audio file relative to the project root.
    Audio(const std::string& path);
    ~Audio();
private:
    MIX_Track* _mixtrack{nullptr};
    MIX_Audio* _mixaudio{nullptr};

    float _volume{1.0f};
    std::size_t _startTime{0};
    std::size_t _pauseTime{0};
    float _speed{1.0f};
    std::string _path{""};
    State _state{State::STOPPED};

    friend class Audio_Manager;
};

class Audio_Manager {
public:
    static bool load(Audio& audio);
    static bool unload(Audio& audio);
    static void clear();
    static bool exists(const Audio& audio);

    /// Play an Audio.
    /// @param audio Audio that needs to be played.
    static void play(Audio& audio);

    /// Pause an Audio.
    /// If it's not being played it does nothing.
    /// @param audio Audio that needs to be paused.
    static void pause(Audio& audio);

    /// Resume an Audio.
    /// If it's not paused it does nothing.
    /// @param audio Audio that needs to be resumed.
    static void resume(Audio& audio);

    /// Stop an Audio.
    /// If it's not being played or paused it does nothing.
    /// @param audio Audio that needs to be stopped.
    /// @param fadeOutFrames Number of fade-out frames before stopping.
    static void stop(Audio& audio, std::uint32_t fadeOutFrames = 0);

    /// Returns the current playback time of an Audio in milliseconds.
    /// @param audio Audio to query.
    static std::size_t getTime(Audio& audio);

    /// Sets the playback time of an Audio in milliseconds.
    /// @param audio Audio to modify.
    /// @param ms Time in milliseconds.
    static void setTime(Audio& audio, std::size_t ms);

    /// Returns the volume of an Audio.
    /// @param audio Audio to query.
    static float getVolume(const Audio& audio);

    /// Sets the volume of an Audio.
    /// @param audio Audio to modify.
    /// @param volume Volume in range [0.0 - 1.0].
    static void setVolume(Audio& audio, float volume);

    /// Changes the volume of an Audio.
    /// @param audio Audio to modify.
    /// @param delta Volume delta in range [-1.0 - 1.0].
    static void changeVolume(Audio& audio, float delta);

    /// Returns the playback speed of an Audio.
    /// @warning Not implemented yet.
    /// @param audio Audio to query.
    static float getSpeed(const Audio& audio);

    /// Sets the playback speed of an Audio.
    /// @warning Not implemented yet.
    /// @param audio Audio to modify.
    /// @param speed Speed factor (0.0 - 5.0).
    static void setSpeed(Audio& audio, float speed);

private:

    /// Initializes SDL_mixer and the Audio Manager system.
    static void _init();

    static void _update(const size_t deltaT);

    static inline MIX_Mixer* _mixmixer{nullptr};
    static inline std::size_t _globalTime{0};

    friend class Window;
};
}
