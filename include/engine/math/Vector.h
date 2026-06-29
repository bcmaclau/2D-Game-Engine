#pragma once

namespace engine {

    class Vec2 {
    public:
        Vec2() : x(0.0f), y(0.0f) {}
        Vec2(float x, float y) : x(x), y(y) {}
        ~Vec2() {}

        float x, y;
        
        Vec2 operator+(const Vec2& other) const;
        
        Vec2& operator+=(const Vec2& other);

        Vec2 operator-(const Vec2& other) const;
        
        Vec2& operator-=(const Vec2& other);

        Vec2 operator*(float scale) const;

        Vec2& operator*=(float scale);

        Vec2 operator/(float scale) const;

        Vec2& operator/=(float scale);

        float magnitude(const Vec2& vec) const;

        Vec2 normalize(const Vec2& vec) const;
    };

}
