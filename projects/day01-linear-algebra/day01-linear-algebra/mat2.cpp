#include "mat2.h"
#include <cmath>
#include <ostream>

Mat2::Mat2(float a, float b, float c, float d) : a(a), b(b), c(c), d(d) {}

Mat2 Mat2::mul(const Mat2& other) const {
    return Mat2(
        a * other.a + b * other.c,  // new a
        a * other.b + b * other.d,  // new b
        c * other.a + d * other.c,  // new c
        c * other.b + d * other.d   // new d
    );
}

Vec2 Mat2::transform(const Vec2& v) const {
    return Vec2(
        a * v.x + b * v.y,
        c * v.x + d * v.y
    );
}

Mat2 Mat2::rotation(float angle_deg) {
    float rad = angle_deg * 3.14159265358979323846f / 180.0f;
    float c = std::cos(rad);
    float s = std::sin(rad);
    return Mat2(c, -s, s, c);
}

std::ostream& operator<<(std::ostream& os, const Mat2& m) {
    os << "[" << m.a << " " << m.b << "]\n"
       << "[" << m.c << " " << m.d << "]";
    return os;
}
