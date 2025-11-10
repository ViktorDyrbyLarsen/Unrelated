import numpy as np

def MyEuler(dxdt, tspan, x0, n):
    """
    Uses Euler's method to integrate an ODE
    
    Input:
    
      dxdt = function handle to the function returning the rhs of the ODE
      
      tspan = [a, b] where a and b are initial and final values of the independent variable
      
      x0 = initial value of dependent variable
     
      n = number of steps
      
    Output:
      t = vector of independent variable
     
      x = [x_0 x_1 ... x_n] vector of solution for dependent variable
    """
    

    a, b = tspan
    t = np.linspace(a, b, n+1)
    h = (b - a) / n # h is calculated only once
    x = np.zeros(n+1) # preallocation for speed
    x[0] = x0 # set initial value
    for i in range(n): # Euler's method
        x[i+1] = x[i] + dxdt(t[i], x[i]) * h
    return t, x
