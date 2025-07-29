#%%
from sympy import *
from typing import Callable, List
init_printing()
#%%
t = symbols('t')
def inner(f,g, interval: tuple=(-pi, pi)):
    # raise NotImplementedError("Inner product not implemented")
    return integrate(f*conjugate(g),(t,-pi,pi))

def GramSchmidtAlgorithm(v: List, inner: Callable, normal: bool = False):
    E = [] #The ortahogonal basis vectors
    for n in range(len(v)):
        if n == 0:
            E.append(v[n])
        else:
            E.append(v[n] - sum([inner(v[n],E[k])/inner(E[k],E[k])*E[k] for k in range(len(E))]))
        if normal:
            E[n] = E[n]/sqrt(inner(E[n],E[n]))
    return Matrix(E)

def represent(v: List, E: List, inner: Callable):
    return sum([inner(v, E[k]) * E[k] for k in range(len(E))])
#%%
if __name__ == "__main__":
    p_5 = [1,t,t**2, t**3,t**4, t**5]
    f = sin(t)

    E = GramSchmidtAlgorithm(p_5, inner, normal=True)
    proj = represent(f, E, inner)

    print("Orthogonal basis:")
    display(E.evalf())
    print("Projection of f onto the space spanned by the basis:")
    print(proj.evalf())
