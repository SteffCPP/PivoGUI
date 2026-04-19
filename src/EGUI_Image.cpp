#include "EGUI_Image.hpp"

namespace egui{
std::string Image::getPath() const { return _path; }
void Image::setPath(const std::string& path){ _path = path; }

Image::Image(const std::string& path){ _path = path; }
Image::Image(){}
}