#%%
import torch
import matplotlib.pyplot as plt
def plot_system(v, x, title="System Evolution"):
    """
    Plot the velocity and position tensors over time.
    
    Args:
        v: Velocity tensor
        x: Position tensor
        title: Plot title (optional)
    """
    time = torch.arange(len(v))
    
    plt.figure(figsize=(10, 6))
    
    plt.subplot(2, 1, 1)
    plt.plot(time, v, 'r-', label='Velocity')
    plt.grid(True)
    plt.legend()
    plt.title(title)
    
    plt.subplot(2, 1, 2)
    plt.plot(time, x, 'b-', label='Position')
    plt.grid(True)
    plt.legend()
    plt.xlabel('Time')
    
    plt.tight_layout()
    plt.show()
#%%
t_end = 100
t_0 = 0
v = torch.empty(t_end - t_0)
x = torch.zeros(t_end - t_0)
delta = 0.1
#%%
x_0 = 0
# %%
for t in range(t_0, t_end):
    v[t] = 1.1 if t > 0 else 1
    x[t] = x[t-1] + v[t]*delta if t > 0 else x_0
plot_system(v, x, "Dynamic System Evolution")
#%%
v, x
# %%
def plot_system(v, x, title="System Evolution"):
    """
    Plot the velocity and position tensors over time.
    
    Args:
        v: Velocity tensor
        x: Position tensor
        title: Plot title (optional)
    """
    time = torch.arange(len(v))
    
    plt.figure(figsize=(10, 6))
    
    plt.subplot(2, 1, 1)
    plt.plot(time, v, 'r-', label='Velocity')
    plt.grid(True)
    plt.legend()
    plt.title(title)
    
    plt.subplot(2, 1, 2)
    plt.plot(time, x, 'b-', label='Position')
    plt.grid(True)
    plt.legend()
    plt.xlabel('Time')
    
    plt.tight_layout()
    plt.show()
#%%
# Example usage
plot_system(v, x, "Dynamic System Evolution")
# %%
x
# %%
