#include "quadtree.h"
#include "atom.h"

Rectangle::Rectangle(double x, double y, double w, double h)
    : x(x), y(y), w(w), h(h) {}

bool Rectangle::contains(const Atom& atom) const {
    // TODO: Implement this method
    return false;
}

bool Rectangle::intersects(const Rectangle& range) const {
    // TODO: Implement this method
    return false;
}

Quadtree::Quadtree(const Rectangle& boundary, int capacity)
    : boundary(boundary), capacity(capacity), divided(false),
      northeast(nullptr), northwest(nullptr), southeast(nullptr), southwest(nullptr) {}

bool Quadtree::insert(Atom& atom) {
    // TODO: Implement this method
    return false;
}

void Quadtree::query(const Rectangle& range, std::vector<Atom*>& found) const {
    // TODO: Implement this method
}

void Quadtree::subdivide() {
    // TODO: Implement this method
}
