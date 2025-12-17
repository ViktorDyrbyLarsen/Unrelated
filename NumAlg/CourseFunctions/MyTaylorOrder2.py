import numpy as np

def MyTaylorOrder2(f, df, tspan, x0, n):
    ti, tf = tspan
    t = np.linspace(ti, tf, n+1)
    x = np.zeros(n+1)   # preallocate x for speed
    x[0] = x0
    h = (tf - ti) / n
    for i in range(n):
        dx = f(t[i], x[i])
        ddx = df(t[i], x[i], dx)
        x[i+1] = x[i] + h * (dx + h/2 * (ddx))
    return t, x
