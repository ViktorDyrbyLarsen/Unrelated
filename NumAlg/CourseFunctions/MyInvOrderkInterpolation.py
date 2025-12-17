import numpy as np
from LagrangeFormInterpolation import LagrangeFormInterpolation

def MyInvOrderkInterpolation(f, x, n):

# MyInvOrderkInterpolation performs n iterations of inverse
# quadratic interpolation for
# a given function f

# x=[x_0,..,x_k-1] are the k initial x-values
# n is the number of iterations
# MyInvOrderkInterpolation returns a vector X with all n estimates
# of the root and a vector containing their function values

    k = len(x)
    fX = np.zeros(n+k)
    X = np.zeros(n+k)
    X[0:k] = x
    for i in range(k):
        fX[i] = f(x[i])
    for i in range(n):
        X[i+k] = LagrangeFormInterpolation(fX[i:i+k], X[i:i+k], [0])
        fX[i+k] = f(X[i+k])
    return X[k:], fX[k:]
