#pragma once

#include <iosfwd>

struct Vec2 {
    float x, y;

    Vec2(float x = 0, float y = 0);

    Vec2 add(const Vec2& other) const;
    float dot(const Vec2& other) const;

    // rotate by angle degrees counter-clockwise, returns new Vec2
    Vec2 rotate(float angle_deg) const;
};

std::ostream& operator<<(std::ostream& os, const Vec2& v);
