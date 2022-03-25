from geocomp.common import prim
from geocomp.common.segment import Segment
from geocomp.common import control

def Brute_force (l):
    filter_segments(l)
    seg = Segment()

    for s in l:
        s.plot()

    for i in range(0, len(l) - 1):
        l[i].hilight(color_line = "blue")
        control.sleep()

        for j in range(i + 1, len(l)):
            l[j].hilight(color_line = "yellow")
            control.sleep()

            if (prim.intersect(l[i].init, l[i].to, l[j].init, l[j].to)):
                l[i].hilight(color_line = "green")
                l[j].hilight(color_line = "green")
                control.sleep()     
                seg.extra_info = "Intersecta"
                return seg

            l[j].plot()

        l[i].plot()

    seg.extra_info = "Não Intersecta"
    return seg

def filter_segments (l):
    for i in range (len(l)):
        if (l[i].init.x > l[i].to.x):
            l[i].init, l[i].to = l[i].to, l[i].init
        elif (l[i].init.x == l[i].to.x):
            if (l[i].init.y > l[i].to.y):
                l[i].init, l[i].to = l[i].to, l[i].init
