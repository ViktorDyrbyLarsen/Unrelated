import numpy as np

def MyHeun(dxdt, tspan, x0, n):
    # Uses Heun's method to integrate an ODE
    # Input:
    #   dydt = function handle to the rhs. of the ODE
    #   tspan = [a, b] where a and b = initial and final values of independent variable
    #   x0 = initial value of dependent variable
    #   n = number of steps
    # Output:
    #   t = vector of independent variable
    #   x = vector of solution for dependent variable

    a, b = tspan
    t = np.linspace(a, b, n+1)
    h = (b - a) / n
    hhalve = h / 2.0 # compute h/2 only once
    x = np.zeros(n+1) # preallocation for speed
    x[0] = x0 # set initial value
    for i in range(n): # Heun's method
        K1 = dxdt(t[i], x[i])
        K2 = dxdt(t[i+1], x[i] + h * K1)
        x[i+1] = x[i] + (K2 + K1) * hhalve
    return t, x