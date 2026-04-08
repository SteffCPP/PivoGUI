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
		extern Color_RGBA Red;
		extern Color_RGBA Green;
		extern Color_RGBA Blue;
		extern Color_RGBA Black;
		extern Color_RGBA White;
		extern Color_RGBA Yellow;
		extern Color_RGBA Cyan;
		extern Color_RGBA Magenta;
		extern Color_RGBA Gray;
		extern Color_RGBA Transparent;
	}
}