#pragma once

#include "mat2.h"
#include "vec2.h"

struct Pose2 {
    Vec2 origin;
    float angleDegrees;

    Vec2 localToWorld(const Vec2& point) const {
        return Mat2::rotation(angleDegrees).transform(point).add(origin);
    }

    Vec2 worldToLocal(const Vec2& point) const {
        const Vec2 offset(point.x - origin.x, point.y - origin.y);
        return Mat2::rotation(-angleDegrees).transform(offset);
    }
};
