#!/usr/bin/env python

from geocomp.common.segment import Segment
from geocomp.common import control
from geocomp.common.guiprim import *
from math import sqrt

MIN_Y = MAX_Y = 0

a = b = mindist = None

def dist_update(x, y):
    global mindist, a, b
    aux = sqrt(dist2(x, y))
    if aux < mindist:
        control.freeze_update()
        if a != None: a.unhilight(dist_update.hia)
        if b != None: b.unhilight(dist_update.hib)
        if dist_update.id != None: control.plot_delete(dist_update.id)

        mindist = aux
        a = x
        b = y

        dist_update.hia = a.hilight()
        dist_update.hib = b.hilight()
        dist_update.id = a.lineto(b)
        control.thaw_update() 
        control.update()

dist_update.hia = None
dist_update.hib = None
dist_update.id = None

def delete_lines(ids):
    for id in ids:
        control.plot_delete(id)
    control.sleep()

def bruteForce(p):
    for i in range(1, len(p)):
        for j in range(i):
            dist_update(p[i], p[j])

def plot_vertical_line(x, color="green"):
    return control.plot_segment(x, MIN_Y, x, MAX_Y, color=color)

def shdistrec(p, q):
    global minsdist
    
    half = len(p) // 2
    center_line_id = plot_vertical_line(p[half][0], "blue")
    control.sleep()

    if len(p) <= 3:
        ids = [plot_vertical_line(p[0][0], "yellow"), plot_vertical_line(p[-1][0], "yellow"), center_line_id]
        bruteForce(p)
        delete_lines(ids)
        return
    
    shdistrec(p[:half], sorted(p[:half], key = lambda point: point[1]))
    shdistrec(p[half:], sorted(p[half:], key = lambda point: point[1]))

    cand = [i for i in q if abs(i[0]-p[half][0]) < mindist]

    left_bound = p[half][0]-mindist
    right_bound = p[half][0]+mindist

    actual_line_id = plot_vertical_line(p[half][0], "yellow")
    right_line_id = plot_vertical_line(right_bound, "green")
    left_line_id = plot_vertical_line(left_bound, "green")
    ids = [actual_line_id, right_line_id, left_line_id, center_line_id]
    control.sleep()

    for i in range(len(cand)-1):
        lower_horizontal_id = control.plot_segment(left_bound, cand[i][1], right_bound, cand[i][1], color="yellow")
        upper_horizontal_id = control.plot_segment(left_bound, cand[i][1]+mindist, right_bound, cand[i][1]+mindist, color="yellow")
        control.sleep()
        j = i + 1
        while j < len(cand) and cand[j][1] - cand[i][1] < mindist:
            dist_update(cand[i], cand[j])
            j += 1
        delete_lines([lower_horizontal_id, upper_horizontal_id])

    delete_lines(ids)

def shdist(p):
    global a, b, mindist, MIN_Y, MAX_Y
    a = b = None
    mindist = float("inf")
    if len(p) < 2: return None
    dist_update(p[0], p[1])

    q = sorted(p, key = lambda point: point[1])
    p.sort(key = lambda point: point[0])

    MIN_Y = q[0][1]
    MAX_Y = q[-1][1]

    shdistrec(p, q)
    a.hilight('green')
    b.hilight('green')
    seg = Segment(a, b)
    seg.extra_info = 'distancia: %.2f'%mindist
    return seg
