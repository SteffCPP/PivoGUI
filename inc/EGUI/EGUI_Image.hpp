#pragma once

#include <string>

struct SDL_Texture;
struct SDL_Surface;

namespace egui{
    class Image{
    public:
        void setPath(const std::string& path){ _path = path; }
        std::string getPath() const { return _path; };

        Image(){}
        Image(const std::string& path){ setPath(path); }
    private:
        std::string _path{""};
    };

    class Animation{

    };
}