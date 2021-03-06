# -*- coding: utf-8 -*-

"""Algoritmos de Geometria Computacional

Sub-modulos:
- closest: algoritmos para encontar o par de pontos mais próximo
- lineintersections: algoritmos para encontrar todas as intersecções de segmentos

- common:     classes e operacoes usadas por diversos algoritmos
- gui:        implementacoes das operacoes graficas
"""

from . import closest
from . import lineintersections
from . import convex_hull
from . import polygons
from . import voronoi
from .common.guicontrol import init_display
from .common.guicontrol import plot_input
from .common.guicontrol import run_algorithm
from .common.prim import get_count
from .common.prim import reset_count

children = (   ( 'lineintersections',  None, 'Interseção de Todos os  Segs' ),
               ( 'closest',  None, 'Par Mais Prox' ),
               ( 'convex_hull', None, 'Fecho Convexo'),
               ( 'polygons', None, 'Polígonos'),
               ( 'voronoi', None, 'Diagrama de Voronoi'),
	)

__all__ = [p[0] for p in children]
