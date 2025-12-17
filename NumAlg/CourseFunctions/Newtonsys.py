import numpy as np

def Newtonsys(FdF, X0, kmax):
    """Solve system f(x) = 0 by Newton's method.

F(x) and F'(x) are computed by the user-supplied function FdF with the
 call [F,dF] = FdF(x), where F is a np.array holding the computed vector F(x) and
 dF is a np.array holding the computed matrix F'(x).

The starting point is x0.
 
The function carries out kmax iterations, and stores all kmax iterations
as columns on the output matrix Xiterations.

Per Christian Hansen and Hans Bruun Nielsen, DTU Compute, April 11, 2016.

Translated to Python spring 2023.

    Args:
        FdF (function): Function that computes F(x) and F'(x). Must return two np.arrays.
        X0 (np.array): The starting point
        kmax (int): Maximal number of iterations

    Returns:
        np.array: Iterations, stored columnwise
    """    

    # Initialization
    X = X0
    Fx, dFx = FdF(X)
    H = np.linalg.solve(dFx,Fx) # This is the first step.
    
    # Create the array to store the iterations.
    
    Xiterations = []
    # Now iterate.
    for k in range(1, kmax+1):
        X = X - H
        Xiterations.append(X)
        Fx, dFx = FdF(X)
        H = np.linalg.solve(dFx,Fx)
    

    return np.array(Xiterations)
