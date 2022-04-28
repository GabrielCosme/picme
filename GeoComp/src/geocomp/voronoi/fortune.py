from geocomp.common.segment import Segment
from geocomp.common.point import Point
from geocomp.common import control
from foronoi import Voronoi, Polygon, VoronoiObserver
from foronoi.events.circle_event import CircleEvent
from foronoi.events.site_event import SiteEvent
import numpy as np

lines = []
plots = []
min_x = 0
max_x = 0
min_y = 0
max_y = 0

def Fortune(P):
    global min_x, max_x, min_y, max_y

    points = [(p.x, p.y) for p in P]

    min_x = min(points, key=lambda p: p[0])[0]
    min_y = min(points, key=lambda p: p[1])[1]
    max_x = max(points, key=lambda p: p[0])[0]
    max_y = max(points, key=lambda p: p[1])[1]

    margin = ((max_x - min_x) + (max_y - min_y)) / 20

    min_x -= margin
    min_y -= margin
    max_x += margin
    max_y += margin

    polygon = Polygon([(min_x, min_y), (max_x, min_y), (max_x, max_y), (min_x, max_y)])

    v = Voronoi(polygon)
    v.attach_observer(VoronoiObserver(callback=lambda a, b: show(v)))
    v.create_diagram(points=points)

def show(voronoi):
    global lines, plots, min_x, max_x

    for line in lines:
        line.unhilight()

    lines.clear()

    edges = voronoi.edges
    sweep_line = voronoi.sweep_line

    for edge in edges:
        plot_edge(edge, sweep_line)
        plot_edge(edge.twin, sweep_line)
    
    if isinstance(voronoi.event, CircleEvent) and voronoi.event.is_valid:
        plot_circle(voronoi.event)
    elif isinstance(voronoi.event, SiteEvent):
        plots.append(Point(voronoi.event.point.x, voronoi.event.point.y).hilight(color="blue"))
    
    plot_beach_line(voronoi)
    plots.append(control.plot_segment(min_x, float(sweep_line), max_x, float(sweep_line)))
    
    control.sleep()
        
    for plot in plots:
        control.plot_delete(plot)

    plots.clear()

def plot_edge(edge, sweep_line):
    global lines

    # Get start and end of edges
    start = edge.get_origin(sweep_line)
    end = edge.twin.get_origin(sweep_line)

    if not (start and end):
        return

    # Draw the line
    lines.append(Segment(Point(start.x, start.y), Point(end.x, end.y)))
    lines[-1].hilight()

def plot_beach_line(voronoi):
    global min_x, max_x, max_y

    arcs = voronoi.arcs
    sweep_line = voronoi.sweep_line

    # Get axis limits
    sweep_line = max_y if sweep_line is None else sweep_line

    # Create 1000 equally spaced points
    x = np.linspace(float(min_x), float(max_x), 1000)

    plot_lines = []

    for arc in arcs:
        plot_line = arc.get_plot(x, sweep_line)

        if plot_line is not None:
            plot_lines.append(plot_line)

    # Plot the bottom of all the arcs
    if len(plot_lines) > 0:
        bottom = np.min(plot_lines, axis=0)
        plots.append(control.plot_curve(x, bottom, color="yellow"))

def plot_circle(event):
    global plots

    x, y = event.center.x, event.center.y
    radius = float(event.radius)

    plots.append(control.plot_circle(x, y, "blue", radius))

    for point in event.point_triple:
        plots.append(Point(point.x, point.y).hilight(color="blue"))
