from geocomp.common.guiprim import float_left
from geocomp.common.segment import Segment
from geocomp.polygons.bst import *
from geocomp.polygons.dcel import *
from geocomp.polygons.monotone import Monotone

MIN_X = MAX_X = 0

def pontaParaBaixo(x, P):
    n = len(P)
    return above((x-1)%n, x, P) and above((x+1)%n, x, P)

def trataCaso1(T, u, v, w, P, dcel):
    if above(w, u, P):
        u, w = w, u

    T, ((i, j), x, (k, l)) = delete(T, v, lambda i: P[i])

    if v == j:
        T = insert(T, v, ((v, w), v, (k, l)), lambda i: P[i])
    else:
        T = insert(T, v, ((i, j), v, (v, w)), lambda i: P[i])

    if pontaParaBaixo(x, P):
        dcel.addEdge(x, v)
        Segment(P[x], P[v]).hilight()
        control.sleep()

    return T

def trataCaso2(T, u, v, w, P, dcel):
    if float_left(P[u], P[v], P[w]):
        u, w = w, u

    T, trap = delete(T, v, lambda i: P[i])

    if trap is None:
        T = insert(T, v, ((v,u), v, (v, w)), lambda i: P[i])
    else:
        (i, j), x, (k, l) = trap

        T = insert(T, v, ((i, j), v, (v, u)), lambda i: P[i])
        T = insert(T, v, ((v, w), v, (k, l)), lambda i: P[i])

        dcel.addEdge(x, v)
        Segment(P[x], P[v]).hilight()
        control.sleep()

    return T

def trataCaso3(T, v, P, dcel):
    T, ((i, j), x, (k, l)) =  delete(T, v, lambda i: P[i])

    if pontaParaBaixo(x, P):
        dcel.addEdge(x, v)
        Segment(P[x], P[v]).hilight()
        control.sleep()

    if j != v or l != v:
        T, ((i_, j_), y, (k_, l_)) = delete(T, v, lambda i: P[i])

        if pontaParaBaixo(y, P):
            dcel.addEdge(y, v)
            Segment(P[y], P[v]).hilight()
            control.sleep()

        if l == v:
            T = insert(T, v, ((i, j), v, (k_, l_)), lambda i: P[i])
        else:
            T = insert(T, v, ((i_, j_), v, (k, l)), lambda i: P[i])

    return T


def plot_horizontal_line(y, color="green"):
    return control.plot_segment(MIN_X, y, MAX_X, y, color=color)

def above(a, b, P):
    return P[a].y > P[b].y or P[a].y == P[b].y and P[a].x > P[b].x

def Monotone_Div(P):
    print(P)
    global MIN_X, MAX_X
    P = P[0].vertices()
    n = len(P)

    MIN_X = min(P, key=lambda p: p.x).x
    MAX_X = max(P, key=lambda p: p.x).x

    E = list(range(n))
    E.sort(key=lambda i: (P[i].y, P[i].x), reverse=True)

    T = None
    dcel = DCEL(P)

    # for face in dcel.findFaces():
    #     print(face)

    for k in range(n):
        v = E[k]
        u = (v - 1) % n
        w = (v + 1) % n

        id = plot_horizontal_line(P[v].y, "blue")
        control.sleep()
        P[v].hilight()

        if above(u, v, P) and above(v, w, P) or above(w, v, P) and above(v, u, P):
            T = trataCaso1(T, u, v, w, P, dcel)
        elif above(v, u, P):
            T = trataCaso2(T, u, v, w, P, dcel)
        else:
            T = trataCaso3(T, v, P, dcel)

        control.plot_delete(id)
        control.sleep()

    for face in dcel.findFaces():
        print(face)
        Monotone(face)
