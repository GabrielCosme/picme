from . import triangulation_n4
from . import triangulation_n3
from . import triangulation_n2
from . import monotone
from . import monotone_div

children = [
    ['triangulation_n4', 'Triangulation_N4', 'Triangulação N4'],
    ['triangulation_n3', 'Triangulation_N3', 'Triangulação N3'],
    ['triangulation_n2', 'Triangulation_N2', 'Triangulação N2'],
    ['monotone', 'Monotone', 'Monótona'],
    ['monotone_div', 'Monotone_Div', 'Div Monótona'],
]

__all__ = [a[0] for a in children]
