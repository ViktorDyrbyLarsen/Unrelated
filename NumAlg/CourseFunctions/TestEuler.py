import numpy as np
from scipy.integrate import solve_ivp
import matplotlib.pyplot as plt
from MyEuler import MyEuler


def odefun(t, x):
    return np.abs(x) 

    
# Define the time span and initial conditions
tspan = [0, 7]
x0 = 0.1     

# Set the number of time steps and calculate the step size
n = 20
h = (tspan[1]-tspan[0])/n
print(f'h: {h}')

t, xt = MyEuler(odefun, tspan, x0, n)

tt = np.linspace(tspan[0], tspan[1])
xx = x0*np.exp(np.abs(tt))

plt.plot(t,xt)
plt.plot(tt,xx)

plt.legend(['Euler', 'Exact'], loc='upper left')
plt.show()