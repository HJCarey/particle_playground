#include "atom.h"
#include <cmath>

Atom::Atom(double x, double y, const std::string& color)
    : color(color) {
    position[0] = x;
    position[1] = y;
    velocity[0] = 0.0;
    velocity[1] = 0.0;
}

double Atom::distance_to(const Atom& other) const {
    double dx = position[0] - other.position[0];
    double dy = position[1] - other.position[1];
    return std::sqrt(dx*dx + dy*dy);
}
