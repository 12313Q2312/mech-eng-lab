#pragma once

#include "vec2.h"
#include <iosfwd>

struct Mat2 {
    // stored as: [ a  b ]
    //            [ c  d ]
    float a, b, c, d;

    Mat2(float a = 1, float b = 0, float c = 0, float d = 1); // identity by default

    Mat2 mul(const Mat2& other) const;
    Vec2 transform(const Vec2& v) const;

    // build a rotation matrix for counter-clockwise rotation by angle_deg
    static Mat2 rotation(float angle_deg);
};

std::ostream& operator<<(std::ostream& os, const Mat2& m);
