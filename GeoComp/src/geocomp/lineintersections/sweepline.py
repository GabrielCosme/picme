from geocomp.common.prim import intersect
from geocomp.common.segment import Segment
from geocomp.common import control
from geocomp import config
from geocomp.lineintersections.bst import *

MIN_Y = MAX_Y = 0

def delete_lines(ids):
    for id in ids:
        control.plot_delete(id)
    control.sleep()

def plot_vertical_line(x, color="green"):
    return control.plot_segment(x, MIN_Y, x, MAX_Y, color=color)

def Sweepline(l):
    global MIN_Y, MAX_Y
    e = []

    for i in range(len(l)):
        if l[i].init.x > l[i].to.x:
            l[i].init, l[i].to = l[i].to, l[i].init
        e += [(l[i].init, i, True)]
        e += [(l[i].to, i, False)]
    e.sort(key=lambda p: p[0].x)

    MIN_Y = min(e, key=lambda p: p[0].y)[0].y
    MAX_Y = max(e, key=lambda p: p[0].y)[0].y

    root = None
    out = False

    for p in range(len(e)):
        i = e[p][1]

        id = plot_vertical_line(e[p][0].x, "yellow")
        control.sleep()

        printTree(root)
        print("-------------")

        pred = predecessor(root, e[p][0], func=lambda k: l[k])
        succ = successor(root, e[p][0], func=lambda k: l[k])

        if e[p][2]:
            root = insert(root, i, func=lambda k: l[k])

            if pred is not None:
                ids = [l[i].hilight(), l[pred.key].hilight()]
                if intersect(l[i].init, l[i].to, l[pred.key].init, l[pred.key].to):
                    out = True
                    break
                delete_lines(ids)

            if succ is not None:
                ids = [l[i].hilight(), l[succ.key].hilight()]
                if intersect(l[i].init, l[i].to, l[succ.key].init, l[succ.key].to):
                    out = True
                    break
                delete_lines(ids)
        else:
            root = delete(root, i, func=lambda k: l[k])

            if pred is not None and succ is not None:
                ids = [l[pred.key].hilight(), l[succ.key].hilight()]
                if intersect(l[pred.key].init, l[pred.key].to, l[succ.key].init, l[succ.key].to):
                    out = True
                    break
                delete_lines(ids)

        control.plot_delete(id)
        control.sleep()

    printTree(root)

    seg = Segment()
    seg.extra_info = "Intersecta" if out else "Não Intersecta"
    return seg
    