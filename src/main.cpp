#include <vector>
#include <SDL.h>
#include <iostream>

#include <cstdlib>  // for rand()
#include <cmath>  // for sqrt and pow

const int WINDOW_SIZE = 800;

class Atom {
public:
    int x, y, vx, vy;
    std::string color;

    Atom(int x, int y, std::string color) : x(x), y(y), vx(0), vy(0), color(color) {}

    double distance_to(const Atom& other) {
        return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));
    }
};

std::vector<Atom> create(int number, std::string color) {
    std::vector<Atom> atoms;
    for (int i = 0; i < number; i++) {
        int x = randomxy(WINDOW_SIZE);
        int y = randomxy(WINDOW_SIZE);
        atoms.push_back(Atom(x, y, color));
    }
    return atoms;
}

int randomxy() {
    return round((double)rand() / RAND_MAX * (WINDOW_SIZE + 1));
}

void rule(std::vector<Atom>& atoms1, std::vector<Atom>& atoms2, double g) {
    for (auto& a : atoms1) {
        int fx = 0;
        int fy = 0;
        for (const auto& b : atoms2) {
            int dx = a.x - b.x;
            int dy = a.y - b.y;
            double d = sqrt(dx*dx + dy*dy);
            if (d > 0 && d < 80) {
                double F = g / d;
                fx += F * dx;
                fy += F * dy;
            }
        }
        a.vx = (a.vx + fx) * 0.5;
        a.vy = (a.vy + fy) * 0.5;
        a.x += a.vx;
        a.y += a.vy;
        if (a.x <= 0 || a.x >= WINDOW_SIZE) {
            a.vx *= -1;
        }
        if (a.y <= 0 || a.y >= WINDOW_SIZE) {
            a.vy *= -1;
        }
    }
}

int main(int argc, char* argv[]) {
    std::vector<Atom> red = create(200, "red");
    std::vector<Atom> green = create(200, "green");

    rule(red, red, -0.1); // Reds attract reds slightly
    rule(red, green, 0.1); // Reds repel greens slightly
    rule(green, red, -0.2); // Greens attract reds strongly

    return 0;
}

