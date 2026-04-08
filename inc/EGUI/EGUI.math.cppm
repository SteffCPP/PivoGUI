#pragma once
#include <cmath>

namespace egui{
	namespace math{
		constexpr double PI = 3.1415926535897932384626;
		constexpr double degToRad(const double __deg){ return __deg*(PI/180); }
		constexpr double radToDeg(const double __rad){ return __rad*(180/PI); }
	}
}