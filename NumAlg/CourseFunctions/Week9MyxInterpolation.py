import numpy as np
from LagrangeFormInterpolation import LagrangeFormInterpolation

def Week9MyxInterpolation(x,y):
    # Week9MyxInterpolation approximates x=y^-1(0)
    #  x descrete x values x_i
    #  y descrete y-values y_i
    n = 3 # number of points used before and after y=0
    # since the projectile starts at height 20, the impact occurs first at time y=0
    # print(y)
    k = np.argwhere(y<0)[0][0]
    # the point of impact lies in the interval y_(k-1) < 0 <= y_k
    ind=np.arange(k-n,k+n,1) # indices of discrete y values before and after y=0
    # use LagrangeFormInterpolation( knots, ydata, x ) 
    x_est=LagrangeFormInterpolation(y[ind],x[ind],[0])
    return x_est