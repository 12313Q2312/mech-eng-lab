#include "mat2.h"
#include "vec2.h"

#include <cmath>
#include <iostream>

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

bool check(const char* name, const Vec2& actual, const Vec2& expected) {
    constexpr float tolerance = 1e-5f;
    const bool ok = std::abs(actual.x - expected.x) <= tolerance
                 && std::abs(actual.y - expected.y) <= tolerance;
    std::cout << (ok ? "PASS " : "FAIL ") << name
              << ": got " << actual << ", expected " << expected << '\n';
    return ok;
}

int main() {
    const Pose2 rotation{{0, 0}, 90};
    const Pose2 translation{{2, 1}, 0};
    const Pose2 toolFrame{{2, 1}, 90};
    const Vec2 point{1, 0};

    bool passed = check("rotate then translate",
                        translation.localToWorld(rotation.localToWorld(point)), {2, 2});
    passed &= check("translate then rotate",
                    rotation.localToWorld(translation.localToWorld(point)), {-1, 3});
    passed &= check("local to world", toolFrame.localToWorld(point), {2, 2});
    passed &= check("world to local", toolFrame.worldToLocal({2, 2}), point);
    return passed ? 0 : 1;
}
