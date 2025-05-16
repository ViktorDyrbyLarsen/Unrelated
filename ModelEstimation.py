#%%
import torch
import matplotlib.pyplot as plt

x = torch.linspace(0, 1, 1000)

def f(x):
    cond1 = (x > 0) & (x < 0.4)
    cond2 = (x > 0.8) & (x < 0.81)
    return torch.where(
        cond1, torch.tensor(1.0),
        torch.where(cond2, torch.tensor(5.0), torch.tensor(0.0))
    )

y = f(x)



# %%
def normalize(y):
    return y / (torch.sum(y))
y = normalize(y)

#%%
from sympy import *
init_printing()
a,b,c,d = symbols('a b c d')
v = Matrix([1,1]); w = Matrix([I,I])
(v+w).norm(2) - (v-w).norm(2)

# %%
(v + I*w).norm(2), (v - I*w).norm(2)
# %%
def inner(v, w):
    return v.T @ w.conjugate()

inner(v, w), inner(v+w, v-w)