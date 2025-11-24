#%%
import torch
import matplotlib.pyplot as plt
from tqdm import tqdm
import numpy as np
# %%
device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')
rng = torch.random.default_generator
#%%
def brownian_motion(T,N, B_0 = 0):
    dt = T / N
    B = torch.zeros(N, device=device)
    B[0] = B_0
    increments = torch.sqrt(torch.tensor(dt,device=device)) * torch.randn(N-1, device=device)
    B[1:] = torch.cumsum(increments, dim = 0) + B_0
    return B

def geometric_brownian_motion(Z0, mu, sigma, T, N):
    B = brownian_motion(T, N)
    t = torch.linspace(0, T, N, device=device)
    Z = Z0 * torch.exp((mu - 0.5 * sigma**2) * t + sigma * B)
    return Z

#%%

def plot_process(X, title = 'Stochastic Process Simulation', xlabel = 't', ylabel = 'X(t)'):
    X = X.detach().to('cpu').numpy() # Makes sure the simulated process is on the CPU and a numpy array
    plt.plot(X, label='X(t)')
    plt.legend()
    plt.title(title)
    plt.xlabel(xlabel)
    plt.ylabel(ylabel)
    plt.show()

Z = geometric_brownian_motion(100, 0.0, 0.2, 1, 1000)
B = brownian_motion(1, 1000)
plot_process(Z)
# plot_process(B, title='Brownian Motion', ylabel='B(t)')



# %%
trials = 1000
data = np.zeros((trials, 1000))
for i in tqdm(range(trials)):
    Z = geometric_brownian_motion(1000, 0.0, 0.2, 1, 1000)
    data[i,:] = Z.detach().to('cpu').numpy()
mean_path = np.mean(data, axis=0)
plt.plot(mean_path, label='Mean Path over 1000 Trials')
plt.title('Mean Path of Geometric Brownian Motion over 1000 Trials')
plt.xlabel('t')
plt.ylabel('Mean Z(t)')
plt.legend()
plt.show()
print(mean_path[-1])
# %%
A = 0.95; B = 1.1
(1 - A**1.05) / (B ** 0.95 - A**1.05)