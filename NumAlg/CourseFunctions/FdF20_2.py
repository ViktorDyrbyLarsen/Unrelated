import numpy as np

def FdF20_2(x, t):
    F = np.array([(x[0] - np.cos(t))**2 + (x[1] - np.sin(t))**2 - 25,
                  (x[0] - np.sin(t))**2 + (x[1] - 6 - np.cos(t))**2 - 25])
    dF = 2 * np.array([[x[0] - np.cos(t), x[1] - np.sin(t)],
                       [x[0] - np.sin(t), x[1] - 6 - np.cos(t)]])
    return F, dF
