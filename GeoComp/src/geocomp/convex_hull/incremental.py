#!/usr/bin/env python

from geocomp.common.polygon import Polygon
from geocomp.common import control
from geocomp.common.guiprim import *

def delete_lines(ids):
    for id in ids:
        control.plot_delete(id)

def draw(h):
    ids = [h[-1].lineto(h[0])]
    for i in range(1, len(h)):
        ids += [h[i-1].lineto(h[i])]
    return ids

def Incremental(p):
    if len(p) < 3: return None

    h = [p[0]]

    if area2(p[0], p[1], p[2]) > 0:
        h += [p[1], p[2]]
    else:
        h += [p[2], p[1]]

    ids = draw(h)
    
    for i in range(3, len(p)):
        hi = p[i].hilight()
        control.update()
        control.sleep()

        n = len(h)
        for j in range(n):
            if area2(h[j], h[(j+1)%n], p[i]) <= 0:
                current = area2(h[-1], h[0], p[i]) > 0
                for a in range(n):
                    next = (area2(h[a], h[(a+1)%n], p[i]) > 0)
                    if current != next:
                        aux = current
                        break
                    current = next

                if current == next:
                    h = [h[0], p[i]]
                    break

                current = next
                for b in range(a+1, n):
                    next = (area2(h[b], h[(b+1)%n], p[i]) > 0)
                    if current != next:
                        break
                    current = next

                if aux:
                    a, b = b, a

                while a != b:
                    h += [h[a]]
                    a = (a+1) % n

                h = h[n:] + [h[a]] + [p[i]]
                break

        delete_lines(ids)
        ids = draw(h)
        p[i].unhilight(hi)

    control.thaw_update() 
    control.update()
    draw(h)

    poly = Polygon(h)
    return poly
