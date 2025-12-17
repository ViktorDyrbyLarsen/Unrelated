def Bisection(f, a, b, nmax):
    # Check input.
    if nmax < 1:
        raise ValueError("nmax must be a positive number")

    # Prepare to iterate.
    if a >= b:
        raise ValueError("a must be less than b")
    fa = f(a)
    fb = f(b)
    if fa * fb > 0:
        raise ValueError("f(a) and f(b) must have different signs")
    X = [0] * (nmax + 1)  # Create X to store the iterations.

    # Iterate.
    for n in range(nmax):
        c = (a + b) / 2  # The midpoint.
        fc = f(c)  # The corresponding function value.
        X[n] = c
        if fa * fc < 0:
            b = c
            # fb = fc  # Note that fb = f(b) is actually not used.
        else:
            a = c
            fa = fc

    # Finish by computing the midpoint of the last interval.
    c = (a + b) / 2
    X[nmax] = c

    return X
