#include "quadtree.h"
#include "atom.h"
#include <vector>
#include <SDL.h>
#include <SDL.h>
#include <iostream>

#include <cstdlib>  // for rand()

const int window_size = 600;

class Boundary {
public:
    Boundary(double x, double y, double w, double h)
        : x(x), y(y), w(w), h(h) {}

    bool contains(const Atom& atom) const {
        return (atom.position[0] >= x - w &&
                atom.position[0] < x + w &&
                atom.position[1] >= y - h &&
                atom.position[1] < y + h);
    }

    bool intersects(const Boundary& range) const {
        return !(range.x - range.w > x + w ||
                 range.x + range.w < x - w ||
                 range.y - range.h > y + h ||
                 range.y + range.h < y - h);
    }

private:
    double x, y, w, h;
};

std::vector<Atom*> create(int number, const std::string& color) {
    std::vector<Atom*> atoms;
    for (int i = 0; i < number; ++i) {
        double x = static_cast<double>(rand()) / RAND_MAX * window_size;
        double y = static_cast<double>(rand()) / RAND_MAX * window_size;
        atoms.push_back(new Atom(x, y, color));
    }
    return atoms;
}

void rule(std::vector<Atom*>& atoms1, std::vector<Atom*>& atoms2, double g) {
    Quadtree quadtree(Rectangle(0, 0, window_size, window_size), 4);
    for (Atom* atom : atoms2) {
        quadtree.insert(*atom);
    }

    for (Atom* a : atoms1) {
        std::vector<Atom*> nearby_atoms;
        quadtree.query(Rectangle(a->position[0], a->position[1], 80, 80), nearby_atoms);

        double force[2] = {0.0, 0.0};
        for (Atom* b : nearby_atoms) {
            double displacement[2] = {a->position[0] - b->position[0], a->position[1] - b->position[1]};
            double distance = a->distance_to(*b);
            if (distance > 0) {
                force[0] += g * displacement[0] / distance;
                force[1] += g * displacement[1] / distance;
            }
        }

        a->velocity[0] = (a->velocity[0] + force[0]) * 0.5;
        a->velocity[1] = (a->velocity[1] + force[1]) * 0.5;
        a->position[0] += a->velocity[0];
        a->position[1] += a->velocity[1];

        if (a->position[0] <= 0 || a->position[0] >= window_size) {
            a->velocity[0] *= -1;
        }
        if (a->position[1] <= 0 || a->position[1] >= window_size) {
            a->velocity[1] *= -1;
        }
    }
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Particle Simulation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_size, window_size, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // TODO: Implement the rest of the function

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
