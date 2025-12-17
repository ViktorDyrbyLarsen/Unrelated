import numpy as np

def cardinalpoly(knots, i, t):
    nodes = np.array(knots)
    t = np.array(t)
    x_i = nodes[i]
    p = 1
    for x_j in np.delete(nodes, i, axis=0):
        p *= (t - x_j) / (x_i - x_j)
    return p