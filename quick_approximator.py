#%%
import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import norm
from tqdm import tqdm

class QuickApproximator:
    def __init__(self, target, initial_guess, func: callable, step_size=0.1, max_std = 1):
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
    
    def bounds(self):
        return self.bounds

    def __call__(self, x):
        # Find the nearest neighbor in the linspace
        if x < self.bounds[0] or x > self.bounds[1]:
            raise ValueError(f"x={x} is out of bounds {self.bounds}")
        idx = np.argmin(np.abs(self.linspace - x))
        return self.values[idx]




func = lambda x: np.exp(x)
revfunc = lambda x: np.log(x)
target = 0.5
approximate = QuickApproximator(target, 10, func, step_size=0.1)
approximate.value(-10), approximate.value(-15)

def GO(target, tolerance=0.0001):
    approximate.target = target
    approximate.state -= 0.1
    for i in (range(10000)):
        approximate.train()
        if abs(approximate.target - approximate.state**2) < tolerance:
            # print(f"Converged at iteration {i}")
            break
    return approximate.state



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
plt.axhline(y=revfunc(target), color='r', linestyle='--', label=f'Target sqrt({approximate.target})=3')
plt.xlabel('Iteration')
plt.ylabel('Value')
plt.title('Approximation History')
plt.legend()
plt.grid(True)
plt.show()
print(revfunc(target) - approximate.state)
# %%
np.random.normal(0,1)
# %%
approximate = QuickApproximator(9, 1)
#%%
approximate.state = 5

#%%

proposals = [approximate.propose() for _ in range(1000)]
plt.hist(proposals, bins=50)
plt.show()
# %%
