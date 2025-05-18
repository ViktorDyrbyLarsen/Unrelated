#%%
from sympy import *

x = Matrix([-1,2]); y = Matrix([1,2])
x.T*y

# %%
B = Matrix.hstack(x, y)
