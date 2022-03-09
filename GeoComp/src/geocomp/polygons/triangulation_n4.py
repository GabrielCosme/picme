from geocomp.common.prim import intersect_prop, left, left_on, right
from geocomp.common.segment import Segment
from geocomp.common import control

def onCone(p, i, j):
    u = (i-1) % len(p)
    w = (i+1) % len(p)

    if left_on(p[u], p[i], p[w]):
        return left(p[i], p[j], p[u]) and left(p[j], p[i], p[w])

    return right(p[i], p[j], p[w]) or right(p[j], p[i], p[u])

def diagonal(p, i, j):
    if not (onCone(p, i, j) and onCone(p, j, i)):
        return False

    for k in range(len(p)):
        l = (k+1) % len(p)
        if k != i and k != j and l != i and l != j:
            if intersect_prop(p[i], p[j], p[k], p[l]):
                return False

    return True

def triang_rec(v):
    if len(v) > 3:
        i = 0
        j = 2
        while not diagonal(v, i, j):
            j += 1
            if j == len(v):
                i += 1
                j = i + 2

        Segment(v[i], v[j]).hilight()
        control.sleep()

        p1 = v[i:j+1]
        p2 = v[:i+1] + v[j:]

        triang_rec(p1)
        triang_rec(p2)

def Triangulation_N4(p):
    v = p[0].vertices()
    triang_rec(v)
