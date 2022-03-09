from geocomp.common.prim import left, right
from geocomp.common.segment import Segment
from geocomp.common import control

def adj(a, b, n):
    c = (a+1) % n
    d = (a-1) % n

    return b in (c, d)

def Monotone(p):
    try:
        v = p[0].vertices()
    except:
        v = p

    i = min(list(range(len(v))), key=lambda i: v[i])
    j = max(list(range(len(v))), key=lambda i: v[i])

    u = list(range(len(v)))

    if i < j:
        l = u[j:] + u[:i]
        r = u[i:j]
    else:
        l = u[j:i]
        r = u[i:] + u[:j]

    is_left = [False] * len(u)
    r.reverse()
    i = j = k = 0

    while k < len(u):
        if i < len(l) and (j == len(r) or v[l[i]] > v[r[j]]):
            u[k] = l[i]
            is_left[l[i]] = True
            i += 1
        else:
            u[k] = r[j]
            is_left[r[j]] = False
            j += 1
        k += 1

    s = [u.pop(0), u.pop(0)]
    d = []

    for i in u:
        id = v[i].hilight()
        control.sleep()

        if not adj(i, s[0], len(v)) and adj(i, s[-1], len(v)):
            while len(s) > 1 and ((is_left[s[-1]] and right(v[i], v[s[-1]], v[s[-2]])) or (not is_left[s[-1]] and left(v[i], v[s[-1]], v[s[-2]]))):
                s.pop()
                d.append(Segment(v[i], v[s[-1]]))
                d[-1].hilight()
                control.sleep()
            s.append(i)

        elif adj(i, s[0], len(v)) and not adj(i, s[-1], len(v)):
            aux = s[-1]
            while len(s) > 1:
                d.append(Segment(v[i], v[s[-1]]))
                d[-1].hilight()
                control.sleep()
                s.pop()
            s.pop()
            s.append(aux)
            s.append(i)

        elif adj(i, s[0], len(v)) and adj(i, s[-1], len(v)):
            s.pop()
            while len(s) > 1:
                d.append(Segment(v[i], v[s[-1]]))
                d[-1].hilight()
                control.sleep()
                s.pop()

        v[i].unhilight(id)
