import pygame
import random
from quadtree import Quadtree

atoms = []
window_size = 600
pygame.init()
window = pygame.display.set_mode((window_size, window_size))

class Boundary:
    def __init__(self, x, y, w, h):
        self.x = x
        self.y = y
        self.w = w
        self.h = h

    def contains(self, atom):
        return (atom.position[0] >= self.x - self.w and
                atom.position[0] < self.x + self.w and
                atom.position[1] >= self.y - self.h and
                atom.position[1] < self.y + self.h)

    def intersects(self, range):
        return not (range.x - range.w > self.x + self.w or
                    range.x + range.w < self.x - self.w or
                    range.y - range.h > self.y + self.h or
                    range.y + range.h < self.y - self.h)


def draw(surface, x, y, color, size):
    for i in range(0, size):
        pygame.draw.line(surface, color, (x, y-1), (x, y+2), abs(size))


import numpy as np

class Atom:
    def __init__(self, x, y, c):
        self.position = np.array([x, y], dtype=np.float64)
        self.velocity = np.array([0.0, 0.0])
        self.color = c

    def distance_to(self, other):
        dx = self.x - other.x
        dy = self.y - other.y
        return (dx*dx + dy*dy)**0.5

def atom(x, y, c):
    return Atom(x, y, c)


def randomxy():
    return round(random.random()*window_size + 1)


def create(number, color):
    group = []
    for i in range(number):
        group.append(atom(randomxy(), randomxy(), color))
        atoms.append((group[i]))
    return group


def rule(atoms1, atoms2, g):
    quadtree = Quadtree(Boundary(0, 0, window_size, window_size), 4)
    for atom in atoms2:
        quadtree.insert(atom)

    for a in atoms1:
        force = np.array([0.0, 0.0])
        nearby_atoms = []
        quadtree.query(Boundary(a.position[0], a.position[1], 80, 80), nearby_atoms)
        for b in nearby_atoms:
            displacement = a.position - b.position
            distance = np.linalg.norm(displacement)
            if distance > 0:
                force += g * displacement / distance
        a.velocity = (a.velocity + force) * 0.5
        a.position += a.velocity
        if a.position[0] <= 0 or a.position[0] >= window_size:
            a.velocity[0] *= -1
        if a.position[1] <= 0 or a.position[1] >= window_size:
            a.velocity[1] *= -1


def main():
    yellow = create(200, "yellow")
    red = create(200, "red")
    green = create(200, "green")
    # blue = create(100, "blue")

    run = True
    while run:
        window.fill(0)

        game = 2

        # Define rules that govern how the particles interact
        # GAME 1: This game uses the following colors:
        #   - red, yellow, green, blue
        # rule(red, red, 0.10)
        # rule(yellow, yellow, -0.10)
        # rule(green, green, 0.05)
        # rule(blue, blue, 0.05)

        # rule(red, yellow, -0.15)
        # rule(green, red, -0.15)
        # rule(red, green, -0.15)
        # rule(green, yellow, 0.15)
        # rule(blue, yellow, 0.15)
        # rule(blue, red, 0.10)

        # GAME 2
        rule(red, red, 0.1)
        rule(yellow, red, 0.15)
        rule(green, green, -0.7)
        rule(green, red, -0.2)
        rule(red, green, -0.1)

        for i in range(len(atoms)):
            draw(window, atoms[i].position[0], atoms[i].position[1], atoms[i].color, 3)

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                run = False
        pygame.display.flip()
    pygame.quit()
    exit()

if __name__ == "__main__":
    main()
