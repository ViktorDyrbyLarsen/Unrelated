#%%
from sympy import *
init_printing()
pi_ = {i: symbols(f"pi_{i}") for i in range(1,4)}
PI = Matrix([pi_[i] for i in range(1,4)]).T
eq = PI*Matrix(3,3,[0,0.75,0.25,0,0.5,0.5,1,0,0]) - PI
normalization = Eq(sum(PI),1)
solve([eq[i] for i in range(3)] + [normalization])