#%%
import numpy as np

class ball:
    def __init__(self, radius: int):
        self.radius = radius

    def print_area(j):
        print(j.radius**2 * np.pi)

b1 = ball(radius = 5)
b2 = ball(radius = 10)

b1.radius = 15# %%
mylist = [1]
output = max(mylist) if mylist else None
if len(mylist):
    output = max(mylist)
else:
    output = None

b1.print_area()
# %%
def printx(x:str) -> int:
    print(type(x))

def func(x,y):
    x = x
    return x

x=1;y=2
# func(self,x=x,y=y)
b1.print_area()

# %%
n = 5
A = np.array([i for i in range(5**2)]).reshape((5,5))
B = np.diag([i for i in range(n)])

print(A)
print(B)

# %%
n = 10
Z = np.zeros((n,n))
O = np.ones((n,n))
# Z[0::2,0::2] += O[0::2,0::2]
# Z[1::2,1::2] += O[1::2,1::2]
A = np.array([i for i in range(3**2)])
print(A)
print(A.reshape((9,1)))
print(A)
A.reshape(3,3)
print(A)

#%%
A = np.array([i for i in range(7**2)]).reshape((7,7))
A = A + 1

#%%
def iseven(x):
    return x % 2 == 0

def isodd(x):
    return not iseven(x)

def checkerboard(A):
    rows = np.shape(A)[0]
    cols = np.shape(A)[1]

    for row in range(rows):
        for col in range(cols):
            if iseven(row) + iseven(col) == 1:
                A[row,col] = 0

    return A

print(checkerboard(A))

#%%
