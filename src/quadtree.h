#ifndef QUADTREE_H
#define QUADTREE_H

#include <vector>

class Atom;

class Rectangle {
public:
    Rectangle(double x, double y, double w, double h);
    bool contains(const Atom& atom) const;
    bool intersects(const Rectangle& range) const;

    double getX() const { return x; }
    double getY() const { return y; }
    double getW() const { return w; }
    double getH() const { return h; }

private:
    double x, y, w, h;
};

class Quadtree {
public:
    Quadtree(const Rectangle& boundary, int capacity);
    bool insert(Atom& atom);
    void query(const Rectangle& range, std::vector<Atom*>& found) const;

private:
    void subdivide();

    Rectangle boundary;
    int capacity;
    std::vector<Atom*> atoms;
    bool divided;
    Quadtree *northeast, *northwest, *southeast, *southwest;
};

#endif // QUADTREE_H
