#include "vec2.h"
#include "mat2.h"
#include <cmath>
#include <ostream>

Vec2::Vec2(float x, float y) : x(x), y(y) {}

Vec2 Vec2::add(const Vec2& other) const {
    return Vec2(x + other.x, y + other.y);
}

float Vec2::dot(const Vec2& other) const {
    return x * other.x + y * other.y;
}

Vec2 Vec2::rotate(float angle_deg) const {
    Mat2 R = Mat2::rotation(angle_deg);
    return R.transform(*this);
}

std::ostream& operator<<(std::ostream& os, const Vec2& v) {
    os << "(" << v.x << ", " << v.y << ")";
    return os;
}
