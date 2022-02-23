#!/usr/bin/env python

from geocomp.common.polygon import Polygon
from geocomp.common import control
from geocomp.common.guiprim import *

def Embrulho(p):
    if len(p) < 3: return None

    end = min(range(len(p)), key = lambda k: p[k].x)
    h = [p[end]]
    i = end

    while True:
        i = (i+1) % len(p)

        hi = h[-1].hilight()
        control.sleep()

        for j in range(len(p)):
            if area2(h[-1], p[i], p[j]) < 0:
                i = j

        h[-1].unhilight(hi)
        h[-1].lineto(p[i])
        
        if i == end:
            break

        h += [p.pop(i)]
        if end > i:
            end -= 1

    poly = Polygon(h)
    return poly
