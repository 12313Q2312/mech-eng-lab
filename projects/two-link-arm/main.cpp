#include "pose2.h"

#include <cmath>
#include <cstdlib>
#include <iostream>

struct ArmPosition {
    Vec2 elbow;
    Vec2 tip;
};

ArmPosition forwardKinematics(float shoulder, float elbow) {
    const Pose2 shoulderFrame{{0, 0}, shoulder};
    const Vec2 elbowPosition = shoulderFrame.localToWorld({2, 0});
    const Pose2 elbowFrame{elbowPosition, shoulder + elbow};
    return {elbowPosition, elbowFrame.localToWorld({1, 0})};
}

bool parseDegrees(const char* input, float& degrees) {
    char* end = nullptr;
    const double value = std::strtod(input, &end);
    if (end == input || *end != '\0' || !std::isfinite(value)) {
        return false;
    }
    degrees = static_cast<float>(std::remainder(value, 360.0));
    return true;
}

bool near(const Vec2& a, const Vec2& b) {
    constexpr float tolerance = 1e-5f;
    return std::abs(a.x - b.x) <= tolerance && std::abs(a.y - b.y) <= tolerance;
}

int main(int argc, char* argv[]) {
    if (argc == 3) {
        float shoulder, elbow;
        if (parseDegrees(argv[1], shoulder) && parseDegrees(argv[2], elbow)) {
            const auto position = forwardKinematics(shoulder, elbow);
            std::cout << "Elbow: " << position.elbow << '\n'
                      << "Tip:   " << position.tip << '\n';
            return 0;
        }
    }
    if (argc != 1) {
        std::cerr << "Usage: two-link-arm [shoulder_deg elbow_relative_deg]\n";
        return 2;
    }

    const struct {
        float shoulder, elbow;
        Vec2 expectedElbow, expectedTip;
    } cases[] = {
        {0, 0, {2, 0}, {3, 0}},
        {90, 0, {0, 2}, {0, 3}},
        {90, -90, {0, 2}, {1, 2}},
        {90, 90, {0, 2}, {-1, 2}},
        {0, 180, {2, 0}, {1, 0}},
    };
    bool passed = true;
    for (const auto& sample : cases) {
        const auto actual = forwardKinematics(sample.shoulder, sample.elbow);
        const bool ok = near(actual.elbow, sample.expectedElbow)
                     && near(actual.tip, sample.expectedTip);
        std::cout << (ok ? "PASS " : "FAIL ") << sample.shoulder << ", "
                  << sample.elbow << " | elbow " << actual.elbow
                  << " | tip " << actual.tip << '\n';
        passed &= ok;
    }
    return passed ? 0 : 1;
}
