#!/usr/bin/env python

from functools import cmp_to_key
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

def Quickhull(p):
    if len(p) < 3: return None

    low = min(range(len(p)), key = lambda k: p[k].y)
    s = [p.pop(low)]
    s += sorted(p, key = cmp_to_key(lambda a, b: -area2(s[0], a, b)))

    h = s[:3]

    ids = draw(h)

    for i in range(3, len(s)):
        hi = s[i].hilight()
        control.update()
        control.sleep()

        for j in range(len(h)-1, -1, -1):
            if area2(h[j], h[j-1], s[i]) < 0:
                break

        h = h[:j+1]
        h += [s[i]]

        delete_lines(ids)
        ids = draw(h)
        s[i].unhilight(hi)

    poly = Polygon(h)
    return poly
