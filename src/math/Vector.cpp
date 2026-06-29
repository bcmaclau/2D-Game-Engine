#include "math/Vector.h"

#include <cmath>

namespace engine {

    Vec2 Vec2::operator+(const Vec2& other) const { return Vec2(x + other.x, y + other.y); }

    Vec2& Vec2::operator+=(const Vec2& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vec2 Vec2::operator-(const Vec2& other) const { return Vec2(x - other.x, y - other.y); }

    Vec2& Vec2::operator-=(const Vec2& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    Vec2 Vec2::operator*(float scale) const { return Vec2(x * scale, y * scale); }

    Vec2& Vec2::operator*=(float scale) {
        x *= scale;
        y *= scale;
        return *this;
    }

    Vec2 Vec2::operator/(float scale) const { return Vec2(x / scale, y / scale); }

    Vec2& Vec2::operator/=(float scale) {
        x /= scale;
        y /= scale;
        return *this;
    }

    float Vec2::magnitude(const Vec2& vec) const { return std::sqrtf(vec.x * vec.x + vec.y * vec.y); }

    Vec2 Vec2::normalize(const Vec2& vec) const { return vec / magnitude(vec); }

}
