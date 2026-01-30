#%%
import torch
import numpy as np
import matplotlib.pyplot as plt

from torch import Tensor
from torchtyping import TensorType
from typing import Callable, List, Optional
#%%
def plot_meshes_in_grid(
    Z_list: List[Tensor | np.ndarray],
    grid_shape: tuple[int, int],
    titles: Optional[List[str]] = None,
    n_cols: int = 3,
    cmap: str = "viridis",
    show_colorbar: bool = True,
    base_size: float = 4.0
):
    """
    Plots a list of 1D flattened 2D outputs (e.g. from bilinear forms on point grids).

    Args:
        Z_list: List of 1D arrays or tensors of shape [H * W].
        grid_shape: Tuple (H, W) defining the shape to reshape each Z into.
        titles: Optional titles for subplots.
        n_cols: Number of columns in the grid.
        cmap: Colormap to use.
        show_colorbar: Whether to show a colorbar.
        base_size: Size of each subplot.
    """
    import matplotlib.pyplot as plt
    import numpy as np

    H, W = grid_shape
    n_plots = len(Z_list)
    n_rows = (n_plots + n_cols - 1) // n_cols
    figsize = (n_cols * base_size, n_rows * base_size)

    fig, axes = plt.subplots(n_rows, n_cols, figsize=figsize)
    axes = np.array(axes).reshape(n_rows, n_cols)

    for idx, Z in enumerate(Z_list):
        row, col = divmod(idx, n_cols)
        ax = axes[row, col]

        Z_np = Z.detach().cpu().numpy() if isinstance(Z, Tensor) else Z
        Z_2d = Z_np.reshape(H, W)

        im = ax.imshow(Z_2d, origin="lower", cmap=cmap, extent=[0, 1, 0, 1])
        if titles:
            ax.set_title(titles[idx])
        if show_colorbar:
            fig.colorbar(im, ax=ax, shrink=0.8)
        ax.set_xticks([])
        ax.set_yticks([])

    for idx in range(n_plots, n_rows * n_cols):
        row, col = divmod(idx, n_cols)
        axes[row, col].axis("off")

    plt.tight_layout()
    plt.show()

#%%
H, W = 100, 100  # height and width of the grid
x = torch.linspace(0, 1, W)
y = torch.linspace(0, 1, H)
mesh = torch.stack(torch.meshgrid(x, y, indexing="xy"), dim=-1)  # [H, W, 2]
points = mesh.reshape(-1, 2)  # [H*W, 2]



def func(X: Tensor,
         Y: Tensor,
         functions: List[Callable[[Tensor, Tensor], Tensor]] | Callable[[Tensor, Tensor], Tensor],
         normalize: bool | List[bool] = True
         ) -> List[np.ndarray]:
    functions = [functions] if callable(functions) else functions
    
    return [function(X, Y).detach().cpu().numpy() for function in functions]



    

functions = [
    lambda X, Y: ,
]

Z_list = func(X, Y, functions)


plot_meshes_in_grid(
    Z_list,
    titles=["Function 1"],
    n_cols=1,
    cmap="viridis",)
# %%
