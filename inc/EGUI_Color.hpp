#pragma once
namespace egui{
	class Color_RGBA{
	public:
		constexpr void setColors(const float R, const float G, const float B, const float A){ _r = R; _g = G; _b = B; _a = A; }
		constexpr void setR(const float R){ _r = R; }
		constexpr void setG(const float G){ _g = G; }
		constexpr void setB(const float B){ _b = B; }
		constexpr void setA(const float A){ _a = A; }

		float getR(){ return _r; }
		float getG(){ return _g; }
		float getB(){ return _b; }
		float getA(){ return _a; }

		Color_RGBA(){}
		Color_RGBA(const float R, const float G, const float B, const float A) : _r(R), _g(G), _b(B), _a(A){}
		~Color_RGBA(){};
	private:
		float _r{0}, _g{0}, _b{0}, _a{0};
	};
}