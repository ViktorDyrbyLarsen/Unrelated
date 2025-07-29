#%%
import torch
from torch.distributions import Laplace
import matplotlib.pyplot as plt

device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
dtype = torch.float32
# %%

gen = torch.Generator(device = device).manual_seed(2450)
mean = torch.tensor(0.0, device=device, dtype=dtype)
scale = torch.tensor(1.0, device=device, dtype=dtype)
    

#%%

samples = Laplace(loc = mean, scale = scale).sample((1000000,))

#%%
moment1 = 1/len(samples) * (samples - torch.zeros_like(samples)).sum()
moment2 = 1/len(samples) * (samples - moment1).sum()

# %%

def laplace_pdf(x):
    x = torch.as_tensor(x, device=device, dtype=dtype)
    return (1/(2*scale)) * torch.exp(-torch.abs(x - mean)/scale)

scaled_pdf = lambda scale, pdf: lambda x: pdf(x / scale) / torch.sqrt(torch.as_tensor(scale, device=device, dtype=dtype))

def plot(samples: torch.Tensor, pdf):
    # Use quantiles to define a focused x-range
    q_low = torch.quantile(samples, 0.001).item()
    q_high = torch.quantile(samples, 0.999).item()
    
    # Add a little margin
    margin = 0.05 * (q_high - q_low)
    x_min = q_low - margin
    x_max = q_high + margin

    x = torch.linspace(x_min, x_max, 1000, device=samples.device, dtype=samples.dtype)
    
    plt.plot(x.cpu().numpy(), pdf(x).cpu().numpy(), label="PDF", color="red")
    plt.hist(samples.cpu().numpy(), bins=100, density=True, alpha=0.5, label="Samples", color="blue")
    plt.title("Laplace Distribution Samples and PDF")
    plt.xlabel("Value")
    plt.ylabel("Density")
    plt.legend()
    plt.show()
#%%
sample_scaled = Laplace(loc = mean, scale = 4*scale).sample((1000000,))
sample_standard = Laplace(loc = mean, scale = scale).sample((1000000,))
# %%
Df = scaled_pdf(4, laplace_pdf)
plot(sample_scaled, Df)
# %%
