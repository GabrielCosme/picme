from geocomp.common.prim import left, left_on, right

# Utils
def onCone(i, j, k, p):
    # Confere se p está no cone formado por i, j, k no sentido anti-horário

    if left_on(k, j, i):
        return left(j, p, k) and left(p, j, i)

    return right(j, p, i) or right(p, j, k)

class Vertex:
    def __init__(self, point):
        self.p = point
        self.hedge = None

    def __repr__(self):
        return "({0}, {1})".format(self.p.x, self.p.y)

class Hedge:
    # v1 -> v2
    def __init__(self, v1, v2):
        self.next = None
        self.twin = None
        self.tail = v1
        self.head = v2
        self.visited = False

    def __repr__(self):
        if self.next is not None:
            return str(self.tail) + "->" + str(self.head)
        else:
            return str(self.tail) + "->()"

class DCEL:
    def __init__(self, points):
        self.vertices = []

        for i, point in enumerate(points):
            self.vertices.append(Vertex(point))

            hedge = Hedge(self.vertices[i-1], self.vertices[i])
            hedge.twin = Hedge(self.vertices[i], self.vertices[i-1])
            hedge.twin.twin = hedge
            hedge.twin.visited = True

            self.vertices[i-1].hedge = hedge

        hedge = Hedge(self.vertices[-1], self.vertices[0])
        hedge.twin = Hedge(self.vertices[0], self.vertices[-1])
        hedge.twin.twin = hedge
        hedge.twin.visited = True

        self.vertices[-1].hedge = hedge

        for i, point in enumerate(points):
            self.vertices[i-1].hedge.next = self.vertices[i].hedge
            self.vertices[i].hedge.twin.next = self.vertices[i-1].hedge.twin

    def addEdge(self, i, j):
        tail = self.vertices[i]
        head = self.vertices[j]

        # Half Edge i->j
        hedge = Hedge(tail, head)
        hedge.twin = Hedge(head, tail)
        hedge.twin.twin = hedge

        # Update the hedges at the tail
        hedge1 = tail.hedge         # hedge1 i->v1
        hedge2 = hedge1.twin.next   # hedge2 i->v2

        # Percorrendo as arestas em torno de tail no sentido horário
        while not onCone(hedge2.head.p, tail.p, hedge1.head.p, head.p):
            hedge1 = hedge2
            hedge2 = hedge2.twin.next

        hedge1.twin.next = hedge
        hedge.twin.next = hedge2

        # Update the hedges at the head
        hedge1 = head.hedge        # hedge1 j->v1
        hedge2 = hedge1.twin.next  # hedge2 j->v2

        # Percorrendo as arestas em torno de head no sentido horário
        while not onCone(hedge2.head.p, head.p, hedge1.head.p, tail.p):
            hedge1 = hedge2
            hedge2 = hedge2.twin.next

        hedge1.twin.next = hedge.twin
        hedge.next = hedge2

    def findFaces(self):
        faces = []

        for vertex in self.vertices:
            hedge = vertex.hedge
            end = hedge

            while True:
                if not hedge.visited:
                    points = []
                    aux = hedge
                    while not aux.visited:
                        points.append(aux.tail.p)
                        aux.visited = True
                        aux = aux.next
                    faces.append(points)

                hedge = hedge.twin.next

                if hedge is end:
                    break

        return faces
