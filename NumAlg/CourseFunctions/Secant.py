def Secant(f, x0, x1, nmax):
    """
    This function implements the secant method to find a root of the function f.
    
    f: the function whose root we want to find
    x0: the initial guess for the root
    x1: the second initial guess for the root
    nmax: the maximum number of iterations
    
    returns: a root of the function f, or None if no root is found
    """
    # Set a tolerance for the error
    tol = 1e-6
    X = [x1]
    # Iterate nmax times
    for n in range(nmax):
        # Compute the value of the function at x0 and x1
        f0 = f(x0)
        f1 = f(x1)
        
        # Compute the secant of the function at x0 and x1
        sec = (x1 - x0) / (f1 - f0)
        
        # Compute the next guess for the root
        x2 = x1 - sec * f1
        X.append(x2)
        # Check if the error is within the tolerance
        if abs(x2 - x1) < tol:
            return X
        
        # Update x0 and x1 for the next iteration
        x0 = x1
        x1 = x2
    
    # If no root was found, return None
    return X
