# -*- coding: utf-8 -*-
"""Algoritmos para o problema do Par Mais Proximo:

Dado um conjunto de pontos S, determinar dois cuja distancia entre eles seja minima

Algoritmos disponveis:
- Forca bruta
"""
from . import brute
from . import shdist

children = [
	[ 'brute', 'Brute', 'Forca Bruta' ],
    ['shdist', 'shdist', 'Distância-SH']
]

__all__ = [a[0] for a in children]
