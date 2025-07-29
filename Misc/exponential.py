#%%
from sympy import *
import numpy as np
import matplotlib.pyplot as plt

init_printing()
# %%
x = symbols('x')
exp0 = lambda x0, y0: (x0, y0)

def exponential(x0, y0, n = 1):
    x = symbols('x')
    exponential = (y0 * (x - x0)**i / factorial(i) for i in range(n+1))

    return sum(exponential)

# %%
exponential(0, 1, 2)
# %%
xshift, yshift = (-2,1)
func = exponential(xshift, 1+yshift, 40)
space = np.linspace(-3, 3, 1000)
y_approx = [func.subs(x, i) for i in space]
y_actual = [np.exp(i - xshift) * yshift for i in space]  # Actual exponential function

plt.figure(figsize=(10, 6))
plt.plot(space, y_approx, label='Exponential Approximation')
plt.plot(space, y_actual, label='Actual exp(x)', linestyle='--')
plt.axhline(0, color='black', lw=0.5, ls='--')
plt.axvline(0, color='black', lw=0.5, ls='--')

# Plot the points (0,1) and (xshift, 1+yshift)
plt.scatter(0, 1, color='red', s=80, zorder=5, label='(0,1)')
plt.scatter(xshift, 1+yshift, color='green', s=80, zorder=5, label=f'({xshift},{1+yshift})')

plt.title('Exponential Approximation vs Actual Exponential')
plt.xlabel('x')
plt.ylabel('y')
plt.legend()
plt.grid()
plt.show()