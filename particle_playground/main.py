import pygame
import random

atoms = []
window_size = 300
pygame.init()
window = pygame.display.set_mode((window_size, window_size))


def draw(surface, x, y, color, size):
    for i in range(0, size):
        pygame.draw.line(surface, color, (x, y-1), (x, y+2), abs(size))


def atom(x, y, c):
    return {
        "x": x,
        "y": y,
        "vx": 0,
        "vy": 0,
        "color": c        
    }


def randomxy():
    return round(random.random()*window_size + 1)


def create(number, color):
    group = []
    for i in range(number):
        group.append(atom(randomxy(), randomxy(), color))
        atoms.append((group[i]))
    return group


def rule(atoms1, atoms2, g):
    for i in range(len(atoms1)):
        fx = 0
        fy = 0
        for j in range(len(atoms2)):
            a = atoms1[i]
            b = atoms2[j]
            dx = a["x"] - b["x"]
            dy = a["y"] - b["y"]
            d = (dx*dx + dy*dy)**0.5
            if(d>0 and d<80):
                F = g/d
                fx += F*dx
                fy += F*dy
        a["vx"] = (a["vx"] + fx) * 0.5
        a["vy"] = (a["vy"] + fy) * 0.5
        a["x"] += a["vx"]
        a["y"] += a["vy"]
        if(a["x"] <= 0 or a["x"] >= window_size):
            a["vx"] *= -1
        if(a["y"] <= 0 or a["y"] >= window_size):
            a["vy"] *= -1


def main():
    yellow = create(100, "yellow")
    red = create(100, "red")

    run = True
    while run:
        window.fill(0)

        # Define rules that govern how the particles interact
        # 1: Reds attracts each other by 0.1
        rule(red, red, 0.1)
        # 2: Red and yellow repel by 0.15
        rule(red, yellow, -0.15)
        # 3: Yellows repel each other by 0.1
        rule(yellow, yellow, -0.1)
        for i in range(len(atoms)):
            draw(window, atoms[i]["x"], atoms[i]["y"], atoms[i]["color"], 3)

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                run = False
        pygame.display.flip()
    pygame.quit()
    exit()

if __name__ == "__main__":
    main()