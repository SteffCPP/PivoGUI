#pragma once
#include <cstdint>
#include <algorithm>

namespace egui{
	class Color_RGBA{
	public:
		constexpr void setColors(const uint32_t R, const uint32_t G, const uint32_t B, const uint32_t A=255){ 
			_r = std::clamp(R, (uint32_t)0, (uint32_t)255);
			_g = std::clamp(G, (uint32_t)0, (uint32_t)255); 
			_b = std::clamp(B, (uint32_t)0, (uint32_t)255); 
			_a = std::clamp(A, (uint32_t)0, (uint32_t)255);
		}

		constexpr uint32_t R() const { return _r; }
		constexpr uint32_t G() const { return _g; }
		constexpr uint32_t B() const { return _b; }
		constexpr uint32_t A() const { return _a; }

		void setR(const uint32_t R){ _r = std::clamp(R, (uint32_t)0, (uint32_t)255); }
		void setG(const uint32_t G){ _g = std::clamp(G, (uint32_t)0, (uint32_t)255); }
		void setB(const uint32_t B){ _b = std::clamp(B, (uint32_t)0, (uint32_t)255); }
		void setA(const uint32_t A){ _a = std::clamp(A, (uint32_t)0, (uint32_t)255); }

		Color_RGBA(){}
		Color_RGBA(const uint32_t R, const uint32_t G, const uint32_t B, const uint32_t A=255){
			setColors(R, G, B, A);
		}
		~Color_RGBA(){};
	private:
		uint32_t _r{0}, _g{0}, _b{0}, _a{255};
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