import numpy as np
from CardinalPolynomial import cardinalpoly
def LagrangeFormInterpolation(knots, ydata, t):
    """
    LagrangeFormInterpolation: Calculates the values of the interpolating polynomial in Lagrange form

    Args:
        knots (list): [x0 x1 ... xn]   is a list of n+1 knot-values
        ydata (list): [y0 y1 ... yn]   is a list of the corresponding n+1 y-values
        t (list): [t1 ... tm]          is a list of m values where the interpolating polynomial is to be evaluated at

    Returns:
        list: [P(t1) ... P(tm)]  a list with m function values of the interpolating polynomial
    """
    
    P_val = []
    cardinals = []
    for idx in range(len(ydata)):
        cardinals.append(cardinalpoly(knots, idx, t))
    np.asarray(cardinals)
    
    P_val = np.zeros(len(t))
    for idx,y in enumerate(ydata):
        P_val = np.add(P_val, np.multiply(cardinals[idx], y))
    
    return P_val