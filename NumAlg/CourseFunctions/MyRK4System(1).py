import numpy as np

def MyRK4System(odefunctions, tspan, X0, n):
    a, b = tspan
    t = a
    X = X0
    h = (b-a)/n
    t_list = [t]
    for j in range(1, n+1):
        K1 = h*odefunctions(t,X)
        K2 = h*odefunctions(t+1/2*h, X+1/2*K1)
        K3 = h*odefunctions(t+1/2*h, X+1/2*K2)
        K4 = h*odefunctions(t+h,X+K3)
        X = X + 1/6*(K1+2*K2+2*K3+K4)
        t = a + j*h
        t_list.append(t)
        X0 = np.vstack((X0,X))
    return t_list, X0