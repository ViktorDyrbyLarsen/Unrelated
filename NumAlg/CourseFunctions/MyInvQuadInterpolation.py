import numpy as np
from LagrangeFormInterpolation import LagrangeFormInterpolation

def MyInvQuadInterpolation(f, x, n):

    # performs n iterations of inverse
    # quadratic interpolation for
    # a given function f
    
    # x=[x0, x1, x2] are the initial x-values
    # n is the number of iterations

    # MyInvQuadInterpolation returns a vector X with all n estimates
    # of the root and a vector containing their function values

    fX = np.zeros(n+3)
    X = np.zeros(n+3)
    X[0:3] = x
    for i in range(3):
        fX[i] = f(x[i])
    for i in range(n):
        X[i+3] = LagrangeFormInterpolation(fX[i:i+3], X[i:i+3], [0])
        fX[i+3] = f(X[i+3])
    return X[3:], fX[3:]
