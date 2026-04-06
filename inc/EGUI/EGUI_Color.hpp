#pragma once
#include <algorithm>
#include <cstdint>

namespace egui{
	class Color_RGBA{
	public:
		constexpr void setColors(const uint8_t R, const uint8_t G, const uint8_t B, uint8_t A){ _r = R; _g = G; _b = B; _a = A; }

		constexpr uint8_t& R(){ return _r; }
		constexpr uint8_t& G(){ return _g; }
		constexpr uint8_t& B(){ return _b; }
		constexpr uint8_t& A(){ return _a; }

		Color_RGBA(){}
		Color_RGBA(const uint8_t R, const uint8_t G, const uint8_t B, uint8_t A=255) : _r(R), _g(G), _b(B), _a(A){}
		~Color_RGBA(){};
	private:
		uint8_t _r{0}, _g{0}, _b{0}, _a{1};
	};

	namespace colors{
		Color_RGBA Red{255, 0, 0};
		Color_RGBA Green{0, 128, 0};
		Color_RGBA Blue{0, 0, 255};
		Color_RGBA Black{0, 0, 0};
		Color_RGBA White{255, 255, 255};
		Color_RGBA Yellow{255, 255, 0};
		Color_RGBA Cyan{0, 255, 255};
		Color_RGBA Magenta{255, 0, 255};
		Color_RGBA Gray{128, 128, 128};
		Color_RGBA Transparent{0, 0, 0, 0};
	}
}