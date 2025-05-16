#%%
import numpy as np
from sympy import *
import matplotlib.pyplot as plt
# %%
space = np.linspace(0,3,1000)

def D(f: Array) -> Array:
    return 

def f(x: Array) -> int:
    return np.where((1 <= x) & (x < 2), 1, 0)

y = f(space)
# %%
plt.plot(space, y, label='f(x)')



# %%
