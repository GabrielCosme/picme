from geocomp.common.prim import intersect_prop, left, left_on, right
from geocomp.common.segment import Segment
from geocomp.common import control

class Node:
    def __init__(self, data, index=None):
        self.data = data
        self.index = index
        self.next = None
        self.prev = None

    def __repr__(self):
        return self.data

class LinkedList:
    def __init__(self, nodes=None):
        self.head = None
        if nodes is not None:
            node = Node(nodes.pop(0), 0)
            self.head = node
            for i, elem in enumerate(nodes):
                aux = node
                node = Node(elem, i+1)
                aux.next = node
                node.prev = aux
            self.head.prev = node
            node.next = self.head

    def __repr__(self):
        if self.head == None:
            return "None"
        node = self.head.next
        nodes = [str(self.head.index)]
        while node is not self.head:
            nodes.append(str(node.index))
            node = node.next
        return " -> ".join(nodes)

def onCone(a, b):
    u = a.prev
    w = a.next

    if left_on(u.data, a.data, w.data):
        return left(a.data, b.data, u.data) and left(b.data, a.data, w.data)

    return right(a.data, b.data, w.data) or right(b.data, a.data, u.data)

def diagonal(p, i, j):
    if not (onCone(i, j) and onCone(j, i)):
        return False

    k = p.head
    while True:
        l = k.next
        if k != i and k != j and l != i and l != j:
            if intersect_prop(i.data, j.data, k.data, l.data):
                return False
        k = l
        if k == p.head:
            break

    return True

def Triangulation_N2(p):
    n = len(p[0].vertices())
    l = LinkedList(p[0].vertices())
    orelha = [None] * n

    while n > 3:
        v2 = l.head

        if orelha[v2.index] is None:
            orelha[v2.index] = diagonal(l, v2.prev, v2.next)

        while not orelha[v2.index]:
            v2 = v2.next
            if orelha[v2.index] is None:
                orelha[v2.index] = diagonal(l, v2.prev, v2.next)

        v1 = v2.prev
        v3 = v2.next
        Segment(v1.data, v3.data).hilight()
        control.sleep()

        v1.next = v3
        v3.prev = v1
        l.head = v3
        n -= 1

        orelha[v1.index] = None
        orelha[v3.index] = None
