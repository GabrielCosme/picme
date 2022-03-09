from geocomp.voronoi.bst import *
from geocomp.voronoi.dcel import *
from geocomp.voronoi.priority_queue import PriorityQueue

def TrataEventoPonto(q, T, Q, V, P):
    if T == None:
        T = insert(T, q, key=lambda i: P[i])
    else:
        f = search(T, q)
        if circle_event(T, f):
            Q.remove(i)
        (u, f , v) = insert(T, q, key=lambda i: P[i])
        V.addAEdge(V, u, None, v, None)
        Q.inset(T, f)

def TrataEventoCírculo(q, T, Q, V, P):
    f = folha(q)
    (pred,suc, novo) = delete(T, f )
    Q.inset(T, f)
    c = centro(q)
    u = (c)
    AdicionaExtremo(V, u, aresta(pred), aresta(suc))
    NovaAresta(V, novo, None, None, u)

def Fortune(P):
    Q = PriorityQueue(P, key=lambda i: P[i].y)
    T = None
    V = DCEL()

    while not Q.empty():
        q = Q.get()
        if q[0] == 'ponto':
            T = TrataEventoPonto(q, T, Q, V, P)
        else:
            T = TrataEventoCírculo(q, T, Q, V, P)

    FinalizeVoronoi(V, T)
    return V
