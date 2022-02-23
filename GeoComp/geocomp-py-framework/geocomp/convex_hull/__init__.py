# -*- coding: utf-8 -*-
"""Algoritmos para o problema do Fecho Convexo:

Dado um conjunto de pontos S, determinar o menor polígono convexo que envolve todos os pontos.

Algoritmos disponveis:
- Incremental
- Embrulho de Presente
- Graham
- Quickhull
"""
from . import incremental
from . import embrulho
from . import graham
from . import quickhull

children = [
	['incremental', 'Incremental', 'Algoritmo Incremental'],
    ['embrulho', 'Embrulho', 'Embrulho de Presente'],
    ['graham', 'Graham', 'Algoritmo de Graham'],
    ['quickhull', 'Quickhull', 'QuickHull']
]

__all__ = [a[0] for a in children]
