import numpy as np

def MyEulerSystem(dxdt, tspan, x0, n):
    
    dim1 = x0.shape[0]
    dim2 = dxdt(tspan[0], x0).shape[0]  # a bit wasteful, but can be saved
    if dim1 - dim2 != 0:
        raise ValueError('The dimensions of x0 and the right side do not match')

    a, b = tspan
    
    t = np.linspace(a, b, n+1)
    h = (b - a) / n  # h is calculated once only
    x = np.zeros((dim1, n+1))  # preallocate x to improve efficiency
    x[:,0] = x0
    for i in range(n):  # Euler's method
        x[:,i+1] = x[:,i] + dxdt(t[i], x[:,i]) * h
    return t, x
