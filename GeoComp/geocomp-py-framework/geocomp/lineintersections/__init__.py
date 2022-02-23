from . import brute_force
from . import sweepline

children = [
    ['brute_force', 'Brute_force', 'Forca Bruta'],
    ['sweepline', 'Sweepline', 'Linha de Varredura']
]

__all__ = [a[0] for a in children]
