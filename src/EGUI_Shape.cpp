#include "EGUI_Shape.hpp"

namespace egui{
inline void Shape::setRotationDegrees(double deg){ 
	_rotationDegrees = deg; 
	_rotationRadians = math::degToRad(deg);
}
inline void Shape::setRotationRadians(double rad){ 
	_rotationRadians = rad;
	_rotationDegrees = math::radToDeg(rad);
}
}
