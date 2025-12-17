import numpy as np

def FdF20_1(X):
    F = np.array([np.sum(X), np.sum(X**2) - 2, X[0]*(X[1]+X[2]) + 1])
    
    dF = np.array([[1, 1, 1], [2*X[0], 2*X[1], 2*X[2]], [X[1]+X[2], X[0], X[0]]])
    
    return F, dF
