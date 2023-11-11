class Rectangle:
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

class Quadtree:
    def __init__(self, boundary, capacity):
        self.boundary = boundary
        self.capacity = capacity
        self.atoms = []
        self.divided = False

    def insert(self, atom):
        if not self.boundary.contains(atom):
            return False
        if len(self.atoms) < self.capacity:
            self.atoms.append(atom)
            return True
        if not self.divided:
            self.subdivide()
        return (self.northeast.insert(atom) or
                self.northwest.insert(atom) or
                self.southeast.insert(atom) or
                self.southwest.insert(atom))

    def query(self, range, found):
        if not self.boundary.intersects(range):
            return
        for atom in self.atoms:
            if range.contains(atom):
                found.append(atom)
        if self.divided:
            self.northeast.query(range, found)
            self.northwest.query(range, found)
            self.southeast.query(range, found)
            self.southwest.query(range, found)

    def insert(self, atom):
        if not self.boundary.contains(atom):
            return False
        if len(self.atoms) < self.capacity:
            self.atoms.append(atom)
            return True
        if not self.divided:
            self.subdivide()
        return (self.northeast.insert(atom) or
                self.northwest.insert(atom) or
                self.southeast.insert(atom) or
                self.southwest.insert(atom))

    def subdivide(self):
        x = self.boundary.x
        y = self.boundary.y
        w = self.boundary.w / 2
        h = self.boundary.h / 2
        ne = Rectangle(x + w, y - h, w, h)
        self.northeast = Quadtree(ne, self.capacity)
        nw = Rectangle(x - w, y - h, w, h)
        self.northwest = Quadtree(nw, self.capacity)
        se = Rectangle(x + w, y + h, w, h)
        self.southeast = Quadtree(se, self.capacity)
        sw = Rectangle(x - w, y + h, w, h)
        self.southwest = Quadtree(sw, self.capacity)
        self.divided = True

    def query(self, range, found):
        if not self.boundary.intersects(range):
            return
        for atom in self.atoms:
            if range.contains(atom):
                found.append(atom)
        if self.divided:
            self.northeast.query(range, found)
            self.northwest.query(range, found)
            self.southeast.query(range, found)
            self.southwest.query(range, found)
