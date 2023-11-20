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
    if (!boundary.contains(atom)) {
        return false;
    }
    if (atoms.size() < capacity) {
        atoms.push_back(&atom);
        return true;
    }
    if (!divided) {
        subdivide();
    }
    return (northeast->insert(atom) ||
            northwest->insert(atom) ||
            southeast->insert(atom) ||
            southwest->insert(atom));
}

void Quadtree::query(const Rectangle& range, std::vector<Atom*>& found) const {
    if (!boundary.intersects(range)) {
        return;
    }
    for (Atom* atom : atoms) {
        if (range.contains(*atom)) {
            found.push_back(atom);
        }
    }
    if (divided) {
        northeast->query(range, found);
        northwest->query(range, found);
        southeast->query(range, found);
        southwest->query(range, found);
    }
}

void Quadtree::subdivide() {
    double x = boundary.x;
    double y = boundary.y;
    double w = boundary.w / 2;
    double h = boundary.h / 2;

    Rectangle ne(x + w, y - h, w, h);
    northeast = new Quadtree(ne, capacity);
    Rectangle nw(x - w, y - h, w, h);
    northwest = new Quadtree(nw, capacity);
    Rectangle se(x + w, y + h, w, h);
    southeast = new Quadtree(se, capacity);
    Rectangle sw(x - w, y + h, w, h);
    southwest = new Quadtree(sw, capacity);

    divided = true;
}
