#%%
from sympy import *
init_printing()
from sympy.abc import x, y, z

#%%
def SVD(A):
    """
    Singular Value Decomposition
    :param A: matrix
    :return: U, S, V
    """
    A_prime = A.H * A
    eigenvalues, eigenvectors = A_prime.eigenvects()

#%%
A = Matrix(3,2, [1,2,2,1,-2,2])
AA_star = A.H * A
eigenvects = AA_star.eigenvects()[0]
v = []
for i in range(len(eigenvects[len(eigenvects)-1])):
    v.append((eigenvects[i], eigenvects[len(eigenvects)-1][i]))
# %%
sigma = Matrix.diag([sqrt(i[0]) for i in v])
sigma
# %%

A = {(i,j): symbols(f'A_{i}{j}') for i in range(3) for j in range(3)}
A = Matrix(3,3, [A[i,j] for i in range(3) for j in range(3)])
A

#%%
A = Matrix(3,2, [1,2,2,1,-2,2])
AA_star = A.H * A
AA_star
# %%
A = Matrix(3,2, [1,2,2,1,-2,2])
AA_star = A.H * A
eigenvects = AA_star.eigenvects()[0]
eigenvects

#%%
a = {i: symbols(f'a_{i}') for i in range(4)}
x = {i: symbols(f'x_{i}') for i in range(2)}
Q = Matrix(2,2, [a[i] for i in range(4)])

x = Matrix(2,1, [x[i] for i in range(2)])
(x.T*Q*x)[0].expand()

# %%
A = Matrix(2,2, [3,-4,4,3])
eigenvects = A.eigenvects()
eigenvects
#%%
eigenbasis = Matrix.hstack(*[eigenvects[i][2][0] / eigenvects[i][2][0].norm() for i in range(len(eigenvects))])
eigenbasis[:,0].T*eigenbasis[:,1].H.T
# %%
