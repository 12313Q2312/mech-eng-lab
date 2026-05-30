#include "vec2.h"
#include "mat2.h"
#include <iostream>
#include <cmath>
#include<cstdlib>

int main() {
    // ---- Test 1: rotate Vec2(1,0) by 90 deg -> expect (0,1) ----
    Vec2 v1(1.0f, 0.0f);
    Vec2 vr = v1.rotate(90.0f);
    std::cout << "Rotate (1,0) by 90 deg: " << vr
              << "  (expect 0,1)" << std::endl;

    // ---- Test 2: vector add & dot ----
    Vec2 a(2.0f, 3.0f);
    Vec2 b(4.0f, -1.0f);
    Vec2 sum = a.add(b);
    float d = a.dot(b);
    std::cout << "(" << a << ") + (" << b << ") = " << sum << std::endl;
    std::cout << "(" << a << ") . (" << b << ") = " << d
              << "  (expect 5)" << std::endl;

    // ---- Test 3: matrix multiply ----
    Mat2 R90 = Mat2::rotation(90.0f);       // [0 -1; 1 0]
    Mat2 R45 = Mat2::rotation(45.0f);       // [0.707 -0.707; 0.707 0.707]
    Mat2 R135 = R90.mul(R45);               // should equal rotation(135)
    Mat2 expected = Mat2::rotation(135.0f);
    std::cout << "R90 * R45 = \n" << R135 << std::endl;
    std::cout << "Expected (R135) = \n" << expected << std::endl;

    // ---- Done ----
    std::cout << "\nAll tests finished." << std::endl;
    system("pause");
    return 0;
}
