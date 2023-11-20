#include "quadtree.h"
#include "atom.h"

Rectangle::Rectangle(double x, double y, double w, double h)
    : x(x), y(y), w(w), h(h) {}

bool Rectangle::contains(const Atom& atom) const {
    return (atom.position[0] >= x - w &&
            atom.position[0] < x + w &&
            atom.position[1] >= y - h &&
            atom.position[1] < y + h);
}

bool Rectangle::intersects(const Rectangle& range) const {
    return !(range.x - range.w > x + w ||
             range.x + range.w < x - w ||
             range.y - range.h > y + h ||
             range.y + range.h < y - h);
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
