#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>

constexpr double gravity = 9.81;
constexpr double length = 1.0;

struct State {
    double angle;
    double angularVelocity;
};

State stepEuler(State state, double dt) {
    const double acceleration = -gravity / length * std::sin(state.angle);
    return {state.angle + dt * state.angularVelocity,
            state.angularVelocity + dt * acceleration};
}

double energy(State state) {
    // Energy per unit mass, with potential zero at the lowest point.
    const double halfSine = std::sin(state.angle / 2);
    const double speed = length * state.angularVelocity;
    return 0.5 * speed * speed + 2 * gravity * length * halfSine * halfSine;
}

struct Drift {
    double finalPercent;
    double peakAbsolutePercent;
};

Drift simulate(State state, double dt, int steps) {
    const double initialEnergy = energy(state);
    double relativePercent = 0;
    double peak = 0;
    for (int i = 0; i < steps; ++i) {
        state = stepEuler(state, dt);
        relativePercent = 100 * (energy(state) - initialEnergy) / initialEnergy;
        peak = std::max(peak, std::abs(relativePercent));
    }
    return {relativePercent, peak};
}

int main() {
    constexpr double pi = 3.141592653589793;
    const State released{pi / 6, 0};
    const Drift coarse = simulate(released, 0.02, 500);
    const Drift fine = simulate(released, 0.005, 2000);
    std::cout << std::fixed << std::setprecision(4)
              << "dt_s,final_drift_pct,max_abs_drift_pct\n"
              << "0.020," << coarse.finalPercent << ',' << coarse.peakAbsolutePercent << '\n'
              << "0.005," << fine.finalPercent << ',' << fine.peakAbsolutePercent << '\n';

    const State equilibrium = stepEuler({0, 0}, 0.02);
    const State first = stepEuler(released, 0.02);
    const bool passed = equilibrium.angle == 0 && equilibrium.angularVelocity == 0
                     && first.angle == released.angle
                     && std::abs(first.angularVelocity - (-0.0981)) < 1e-12
                     && std::isfinite(coarse.finalPercent) && std::isfinite(fine.finalPercent)
                     && fine.finalPercent > 0
                     && fine.peakAbsolutePercent < coarse.peakAbsolutePercent;
    return passed ? 0 : 1;
}
