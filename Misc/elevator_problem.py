#%%
import numpy as np
from tqdm import tqdm
#%%
floors = 10
workers = 12

def sample(floors, workers):
    # Sample a random number of workers on each floor
    return len(set(np.random.randint(0, workers + 1, size=floors)))
#%%
sample(floors, workers)

# %%
N = 1000000
samples = np.zeros(N)
for i in tqdm(range(N)):
    samples[i] = sample(floors, workers)

print(f"Mean: {samples.mean()}")
print(f"Standard deviation: {samples.std()}")

#%%
#Probability of a floor being selected
I_emptyfloor = ((floors - 1)/floors)**workers
I_floor = (1 - I_emptyfloor)
# Expected number of floors
E_floors = floors * I_floor
print(f"Expected number of floors: {E_floors}")
#%% Compared to the simulation
print(f"Expected number of floors: {samples.mean() - E_floors}")
# %%
