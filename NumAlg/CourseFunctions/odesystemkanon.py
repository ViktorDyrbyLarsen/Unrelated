import numpy as np
def odesystemkanon( _ , indata ):
    """
    simultaneous second order differentials for projectile
    motion with air resistance
    output vector z has the four differential outputs
    assumed units: metres, seconds, Newtons, kg, radians
    since the first variable t is not used 
    it can be replaced by _ in the function call
    """

    g=9.81 # m/s^2
    m=550/1000 # mass of projectile, kg
    d=0.07 # diameter of spherical projectile, meters
    Cd=0.5 # assumed
    rho=1.2041 # density of air, kg/m^3
    A=(np.pi*d**2)/4 # silhouette area, m^2
    C=Cd*A*rho/2/m # the drag force constant
    z = np.zeros(4) # initialize space

    z[0] = indata[1]
    z[1] = (-C) * np.sqrt(indata[1]**2 + indata[3]**2)*indata[1]
    z[2] = indata[3]
    z[3] = (-g/m) + ((-C) * np.sqrt(indata[1]**2 + indata[3]**2) * indata[3])
    
    return z