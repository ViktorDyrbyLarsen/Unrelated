import numpy as np

def MyRK4(dxdt, tspan, x0, n):

    a = tspan[0]
    b = tspan[1]
    t = np.linspace(a, b, n + 1)
    h = (b - a) / n
    h2 = h / 2.0
    h6 = h / 6.0
    x = np.ones((n + 1)) * x0 # preallocate x to improve efficiency
    for i in range(n): # implement the method
        K1 = dxdt(t[i], x[i])
        K2 = dxdt(t[i] + h2, x[i] + h2 * K1)
        K3 = dxdt(t[i] + h2, x[i] + h2 * K2)
        K4 = dxdt(t[i + 1], x[i] + h * K3)
        x[i + 1] = x[i] + h6 * (K1 + 2 * (K2 + K3) + K4)
    
    return t, x
