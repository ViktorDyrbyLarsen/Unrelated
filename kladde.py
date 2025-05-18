#%%
from sympy import *

x = Matrix([-1,2])
v = Matrix([1,2])
a,b,c,d = symbols('a b c d')
A = Matrix([[a,b],[c,d]])
solve(((A*x).T * v)[0] - v.norm())
