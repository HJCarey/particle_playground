#include <vector>
#include <SDL.h>
#include <iostream>

#include <cstdlib>  // for rand()

class Atom {
public:
    int x, y;
    std::string color;

    Atom(int x, int y, std::string color) : x(x), y(y), color(color) {}

    double distance_to(const Atom& other) {
        return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));
    }
};

std::vector<Atom> create(int number, std::string color) {
    std::vector<Atom> atoms;
    for (int i = 0; i < number; i++) {
        int x = rand() % 100;  // replace with your own logic
        int y = rand() % 100;  // replace with your own logic
        atoms.push_back(Atom(x, y, color));
    }
    return atoms;
}

void rule(std::vector<Atom>& atoms1, std::vector<Atom>& atoms2, double g) {
    // replace with your own logic to calculate the force between atoms
    // and update their positions and velocities accordingly
}

int main(int argc, char* argv[]) {
    std::vector<Atom> red = create(200, "red");
    std::vector<Atom> green = create(200, "green");

    double g = 0.1;  // replace with your own value
    rule(red, green, g);

    return 0;
}
