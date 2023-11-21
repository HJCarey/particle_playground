#ifndef ATOM_H
#define ATOM_H

#include <string>

class Atom {
public:
    Atom(double x, double y, const std::string& color);
    double distance_to(const Atom& other) const;

public:
    double position[2];
    double velocity[2];
private:
    std::string color;
};

#endif // ATOM_H
