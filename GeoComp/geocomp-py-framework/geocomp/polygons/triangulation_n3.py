from geocomp.common.segment import Segment
from geocomp.common import control
from geocomp.polygons.triangulation_n4 import diagonal

def Triangulation_N3(p):
    v = p[0].vertices()

    while len(v) > 3:
        i = 0
        while not diagonal(v, (i-1)%len(v), (i+1)%len(v)):
            i += 1
        Segment(v[(i-1)%len(v)], v[(i+1)%len(v)]).hilight()
        control.sleep()
        v.pop(i)
