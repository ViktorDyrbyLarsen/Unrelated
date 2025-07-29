#%%
import numpy as np
import matplotlib.pyplot as plt

dist = {
    'sample': lambda n: np.random.normal(loc=0, scale=1, size=n), 'mean': 0, 'variance': 1
        }

def experiment(n: int, dist: dict):
    data = dist['sample'](n)
    mean = dist['mean']
    variance = dist['variance']
    time_series = np.cumsum(data) / np.arange(1, n + 1)
    return {
        'data': data,
        'mean': mean,
        'variance': variance,
        'time_series': time_series
    }

def plot_experiment(experiment_data):
    n = len(experiment_data['time_series'])
    x = np.arange(1, n + 1)
    
    # Calculate standard error bounds (standard deviation of the mean)
    std_error = np.sqrt(experiment_data['variance'] / x)
    
    plt.figure(figsize=(12, 6))
    plt.plot(experiment_data['time_series'], label='Sample Mean', color='blue')
    plt.axhline(y=experiment_data['mean'], color='red', linestyle='--', label='Expected Mean')
    
    # Add standard deviation bounds
    plt.fill_between(
        x, 
        experiment_data['mean'] - std_error, 
        experiment_data['mean'] + std_error, 
        alpha=0.2, 
        color='green', 
        label='±1 Standard Error'
    )
    
    plt.title('Law of Large Numbers Experiment')
    plt.xlabel('Number of Samples')
    plt.ylabel('Sample Mean')
    plt.legend()
    plt.grid()
    plt.show()

if __name__ == "__main__":
    ex = experiment(100, dist)
    print(f"Sample Mean: {np.mean(ex['data'])}, Expected Mean: {ex['mean']}")
    print(f"Sample Variance: {np.var(ex['data'])}, Expected Variance: {ex['variance']}")
    plot_experiment(ex)

