#%%
import torch
import matplotlib.pyplot as plt
from tqdm import tqdm
# %%
device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')
rng = torch.random.default_generator
#%%

mean = 0.01
nodes_amount = 5
layers = 3
nodes = torch.zeros(nodes_amount).to(device)

# def graph(nodes: int, layers: int, edges: dict = None):

# np.mean(diff)

#%%
plt.plot(S, label='S')
plt.legend()
plt.title('Stochastic Process Simulation')
plt.xlabel('Time/index')
plt.ylabel('Value')
plt.show()
# %%
