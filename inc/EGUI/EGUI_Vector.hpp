/*
EGUI - Easy Graphical User Interface
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

namespace egui{
	/// Represents a 2D vector with float precision.
/// Used for positions, sizes, directions and basic 2D math.
struct Vector2D {
    float x{0}; ///< X component.
    float y{0}; ///< Y component.

    /// Vector addition.
    /// @param v Vector to add.
    /// @return Resulting vector (x + v.x, y + v.y).
    constexpr Vector2D operator+(const Vector2D& v) const {
        return { x + v.x, y + v.y };
    }

    /// Vector subtraction.
    /// @param v Vector to subtract.
    /// @return Resulting vector (x - v.x, y - v.y).
    constexpr Vector2D operator-(const Vector2D& v) const {
        return { x - v.x, y - v.y };
    }

    /// Component-wise multiplication.
    /// @param v Vector to multiply.
    /// @return Resulting vector (x * v.x, y * v.y).
    constexpr Vector2D operator*(const Vector2D& v) const {
        return { x * v.x, y * v.y };
    }

    /// Scalar multiplication.
    /// @param s Scalar value.
    /// @return Scaled vector (x * s, y * s).
    constexpr Vector2D operator*(float s) const {
        return { x * s, y * s };
    }

    /// Component-wise division.
    /// @param v Vector divisor.
    /// @return Resulting vector (x / v.x, y / v.y).
    constexpr Vector2D operator/(const Vector2D& v) const {
        return { x / v.x, y / v.y };
    }

    /// Scalar division.
    /// @param s Scalar divisor.
    /// @return Scaled vector (x / s, y / s).
    constexpr Vector2D operator/(float s) const {
        return { x / s, y / s };
    }
};
} 
