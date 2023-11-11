import pygame
import random
from quadtree import Quadtree

atoms = []
window_size = 1200
pygame.init()
window = pygame.display.set_mode((window_size, window_size))

class Boundary:
    def __init__(self, x, y, w, h):
        self.x = x
        self.y = y
        self.w = w
        self.h = h

    def contains(self, atom):
        return (atom.x >= self.x - self.w and
                atom.x < self.x + self.w and
                atom.y >= self.y - self.h and
                atom.y < self.y + self.h)

    def intersects(self, range):
        return not (range.x - range.w > self.x + self.w or
                    range.x + range.w < self.x - self.w or
                    range.y - range.h > self.y + self.h or
                    range.y + range.h < self.y - self.h)


def draw(surface, x, y, color, size):
    for i in range(0, size):
        pygame.draw.line(surface, color, (x, y-1), (x, y+2), abs(size))


class Atom:
    def __init__(self, x, y, c):
        self.x = x
        self.y = y
        self.vx = 0
        self.vy = 0
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
        fx = 0
        fy = 0
        nearby_atoms = []
        quadtree.query(Boundary(a.x, a.y, 80, 80), nearby_atoms)
        for b in nearby_atoms:
            dx = a.x - b.x
            dy = a.y - b.y
            d = a.distance_to(b)
            if d > 0:
                F = g/d
                fx += F*dx
                fy += F*dy
        a.vx = (a.vx + fx) * 0.5
        a.vy = (a.vy + fy) * 0.5
        a.x += a.vx
        a.y += a.vy
        if a.x <= 0 or a.x >= window_size:
            a.vx *= -1
        if a.y <= 0 or a.y >= window_size:
            a.vy *= -1


def main():
    yellow = create(100, "yellow")
    red = create(500, "red")
    green = create(500, "green")

    run = True
    while run:
        window.fill(0)

        # Define rules that govern how the particles interact
        rule(red, red, 0.1)
        rule(red, yellow, -0.15)
        rule(yellow, yellow, -0.1)
        rule(green, green, 0.05)
        rule(green, red, -0.15)
        rule(green, yellow, 0.15)

        for i in range(len(atoms)):
            draw(window, atoms[i].x, atoms[i].y, atoms[i].color, 3)

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                run = False
        pygame.display.flip()
    pygame.quit()
    exit()

if __name__ == "__main__":
    main()
