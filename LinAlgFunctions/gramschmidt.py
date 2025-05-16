#%%
from sympy import *
init_printing()

t = symbols('t')
def inner(f,g):
    # raise NotImplementedError("Inner product not implemented")
    return integrate(f*conjugate(g),(t,-1,1))

def GramSchmidtAlgorithm(v: list, inner: callable, normal = False):
    E = [] #The ortahogonal basis vectors
    for n in range(len(v)):
        if n == 0:
            E.append(v[n])
        else:
            E.append(v[n] - sum([inner(v[n],E[k])/inner(E[k],E[k])*E[k] for k in range(len(E))]))
        if normal:
            E[n] = E[n]/sqrt(inner(E[n],E[n]))
    return Matrix(E)


if __name__ == "__main__":
    p_2 = [1,t,t**2]
    p_3 = [1,t,t**2,t**3]
    O_2 = GramSchmidtAlgorithm(p_2,inner,normal=True)
    O_3 = GramSchmidtAlgorithm(p_3,inner,normal=True)
    print(symbols("O_2"), O_2, symbols("O_3"), O_3)
