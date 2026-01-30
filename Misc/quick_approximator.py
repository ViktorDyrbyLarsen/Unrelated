#%%
import numpy as np
import matplotlib.pyplot as plt
from tqdm import tqdm
from typing import Callable
class QuickApproximator:
    def __init__(self, target, initial_guess, func: Callable[[float], float], step_size=0.1, max_std = 1):
        self.func = func
        self.state = initial_guess
        self.history = [initial_guess]
        self.valuehistory = []
        self.target = target
        self.max_std = max_std
        self.step_size = step_size

    def value(self, x = None):
        if x is None:
            x = self.state
        # Calculate the value of the function at x
        return abs(self.target - self.func(x))

    def propose(self):
        error = self.value(self.state)
        std = min(error * self.step_size, self.max_std)
        proposal = np.random.normal(self.state, std)
        return proposal
    
    def train(self):
        proposal = self.propose()
        if self.value(proposal) < self.value(self.state):
            # Accept the proposal
            self.state = proposal
            self.history.append(proposal)
        else:
            # Reject the proposal
            # self.state = proposal
            self.history.append(self.state)
        self.valuehistory.append(self.value())


#%%
class NearestNeighborFunction:
    def __init__(self, linspace, values):
        self.linspace = linspace
        self.values = values
        self.bounds = (linspace[0], linspace[-1])
    

    def __call__(self, x):
        # Find the nearest neighbor in the linspace
        if x < self.bounds[0] or x > self.bounds[1]:
            raise ValueError(f"x={x} is out of bounds {self.bounds}")
        idx = np.argmin(np.abs(self.linspace - x))
        return self.values[idx]




func = lambda x: x**2
revfunc = lambda x: np.sqrt(x)
target = 5
approximate = QuickApproximator(target, 10, func, step_size=0.1)
# approximate.value(-10), approximate.value(-15)

def GO(target, tolerance=0.0001):
    approximate.target = target
    approximate.state -= 0.1
    for i in (range(10000)):
        approximate.train()
        if abs(approximate.target - approximate.state**2) < tolerance:
            # print(f"Converged at iteration {i}")
            break
    return approximate.state
print(GO(target, 0.0001))
#%%

X = np.linspace(1, np.pi, 100)
Y = X.copy()
for i, x in tqdm(enumerate(X)):
    Y[i] = abs(GO(x, 0.0000001))

sqrt = NearestNeighborFunction(X, Y)
#%%
plt.plot(X, Y)
#%%
sqrt(3)
#%%

#%%
np.max(func(X) - Y)

#%%
# Plot the history of states
plt.figure(figsize=(10, 6))
plt.plot(approximate.history)
plt.axhline(y=revfunc(target), color='r', linestyle='--', label=f'Target sqrt({round(approximate.target,5)})={round(np.sqrt(approximate.target),5)}')
plt.xlabel('Iteration')
plt.ylabel('Value')
plt.title('Approximation History')
plt.legend()
plt.grid(True)
plt.show()
print(revfunc(target) - approximate.state)
# %%

proposals = [approximate.propose() for _ in range(10000)]
plt.hist(proposals, bins=50)
plt.show()
# %%
if __name__ == "__main__":
    target = 5
    initial_guess = 2.3
    func = lambda x: x**2
    approximator = QuickApproximator(target, initial_guess, func)
    approximator.train()
    print(f"Final approximation: {approximator.state}")

# %%
