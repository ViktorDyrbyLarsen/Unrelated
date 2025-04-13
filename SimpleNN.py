#%%
import numpy as np
import random
from tqdm import tqdm
import matplotlib.pyplot as plt
#%%
class NN:
    def __init__(self, layers: np.array, activation: callable = lambda x: np.maximum(0,x), output_activation: callable = lambda a: a):
        rng = np.random.default_rng()
        self.layers = layers #We define the number of neurons in each layer such that layers[l] gives the number of neurons.
        self.output_activation = output_activation
        self.activation = activation
        self.W = {l: rng.standard_normal((self.layers[l+1],self.layers[l])) for l in range(len(self.layers)-1)} #Weight matrix for each layer
        self.b = {l: rng.standard_normal((self.layers[l+1],1)) for l in range(len(self.layers)-1)}

    def forward(self, x: np.array):
        x = np.reshape(x, (self.layers[0], 1))
        self.a = {0: x}
        self.z = {}

        for l in range(len(self.layers)-1):
            z = self.W[l] @ self.a[l] + self.b[l]
            if l == len(self.layers) - 2:
                a = self.output_activation(z)
            else:
                a = self.activation(z)
            self.z[l+1] = z
            self.a[l+1] = a

        return a
    
    def d_relu(self,z):
        return (z > 0).astype(float)

    def backprop(self, pred, target):

        grads_W = {}
        grads_b = {}
        target = np.reshape(target,(target.size,1))
        assert pred.shape == target.shape, f"Prediction shape {pred.shape} doesn't match target {target.shape}"
        delta = 2 * (pred - target)
        L = len(self.layers) - 1

        for l in reversed(range(L)):
            z = self.z[l+1]
            a_prev = self.a[l]

            if l != L - 1:
                delta = delta * self.d_relu(z)

            grads_W[l] = delta @ a_prev.T
            grads_b[l] = delta

            if l > 0:
                delta = self.W[l].T @ delta
        return grads_W, grads_b

    def update(self, grads_W, grads_b, step_size = 10**-6):
        for l in range(len(self.layers) - 1):
            self.W[l] -= step_size * grads_W[l]
            self.b[l] -= step_size * grads_b[l]

    def train(self, training_data, N, stats = False):
        if stats:
            L = np.empty(N)
        for n in tqdm(range(N)):
            x, y = random.choice(training_data)
            y_hat = self.forward(x)
            grads_W, grads_b = self.backprop(y_hat,y)
            self.update(grads_W,grads_b)
            if stats:
                L[n] = np.mean((y_hat - y)**2)
        
        if stats:
            return L

#%%
model = NN(np.array([2, 42, 32, 50, 2]), output_activation=lambda x: x)  # identity output for regression
model_simpler = NN(np.array([2, 32, 32, 2]), output_activation=lambda x: x)
n = 10000
train = []
crazy_train = []
rng = np.random.default_rng()

for _ in range(n):
    x = rng.uniform(-6, 5, 2)
    train.append((x, np.array([x[0]*x[1] + 3, x[0]**2 - 3*x[1]**3])))
    crazy_train.append((x, np.array([np.sqrt(np.abs(x[1])) * x[0]**2 + 24,
                                     np.cos(np.abs(x[1])/6*np.pi/1.8)*x[0] - x[0] - 12 + np.exp(np.clip(x[0], -5, 2))])))

ys = np.array([y for _, y in crazy_train])
y_mean = ys.mean(axis=0)
y_std = ys.std(axis=0)

crazy_train_normalized = [(x.reshape(-1, 1), ((y - y_mean) / y_std).reshape(-1, 1)) for x, y in crazy_train]
#%%
def plot_loss(loss_values, model):
    plt.figure(figsize=(10, 4))
    plt.plot(loss_values)
    plt.xlabel("Iteration")
    plt.ylabel("Mean Squared Error")
    plt.title(f"Training Loss Over Time for {model}")
    plt.grid(True)
    plt.tight_layout()
    plt.show()
#%%
# L = model.train(train, 100000, stats=True)
n = 10000
rate = 10*-4
L_crazy = model.train(crazy_train_normalized, 1000, stats=True)
L_crazy_simpler = model_simpler.train(crazy_train_normalized, 1000, stats=True)
plot_loss(L_crazy, "complex model")
plot_loss(L_crazy_simpler, "simpler model")

# %%
