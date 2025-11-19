#%%
import torch
import matplotlib.pyplot as plt
from tqdm import tqdm
# %%
device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')
rng = torch.random.default_generator
#%%

mean = 0
nodes_amount = 5
layers = 3
nodes = torch.zeros(nodes_amount).to(device)

# make a fake stochastic process S
T = 200  # length

increments = mean + 0.05 * torch.randn(T, device=device)
S = torch.cumsum(increments, dim=0).cpu()  # move to cpu for plotting


plt.plot(S, label='S')
plt.legend()
plt.title('Stochastic Process Simulation')
plt.xlabel('Time/index')
plt.ylabel('Value')
plt.show()
# %%
