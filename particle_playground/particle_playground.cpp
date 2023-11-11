#include <vector>
#include <random>
#include <array>

class Atom {
public:
    std::array<double, 2> position;
    std::array<double, 2> velocity;
    std::string color;

    Atom(double x, double y, std::string c) : position{x, y}, velocity{0.0, 0.0}, color(c) {}
};

std::vector<Atom> create(int number, std::string color, int window_size) {
    std::vector<Atom> group;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(1, window_size);

    for (int i = 0; i < number; ++i) {
        group.push_back(Atom(dis(gen), dis(gen), color));
    }
    return group;
}
