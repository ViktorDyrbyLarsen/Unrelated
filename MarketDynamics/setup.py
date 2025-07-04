#%% Imports
import torch

#%% Base Environment Class. Should be updated as I develop the environment further.
class MarketEnv:
    """
    A base data structure that holds complete information about the environment.

    Args:
        n_agents (int): The number of agents in the environment.
        n_ressources (int): The number of different ressources in the environment .
        device (str or torch.device, optional): Device to use ("cuda" or "cpu"). Default is "cpu".
        float_dtype (torch.dtype, optional): specify torch float dtype to use. Default is torch.float32.
        debug (bool): turns on safety checks for easier debugging. Default is True
    """
    
    def __init__(self,
                 n_agents: int,
                 n_ressources: int,
                 device: str | torch.device = "cpu",
                 float_dtype: torch.dtype = torch.float32,
                 debug: bool = True
                 ) -> None:
        
        # Device and precision settings
        self.device = torch.device(device)
        self.dtype = float_dtype

        # Debugging mode
        self.debug = debug
        
        # Set metadata for easier reference
        self.n_agents = n_agents
        self.n_ressources = n_ressources

        # Define attribute dict to map names to correct indices
        # Attribute indices: each agent-resource pair tracks these quantities
        # inventory: how much of the resource the agent has
        # demand: how much the agent wants this resource (float, dynamic)
        # income: resource flow to the agent per step (optional)
        # needs: whether this resource is required by the agent (binary)
        self.attribute_schema = {
                                 "inventory": {"idx": 0, "type": "float"} ,
                                 "demand": {"idx": 1, "type": "float"}    ,
                                 "income": {"idx": 2, "type": "float"}    ,
                                 "needs": {"idx": 3, "type": "bool"}      ,
                                }
        

        # Defining the environment
        self.env = torch.zeros((n_agents, n_ressources, len(self.attribute_schema)), device=device, dtype=self.dtype)

    def get_attribute_table(self, attribute_to_get: str | int) -> torch.Tensor:
        """
        Allows accessing attribute tables

        Args:
            attribute_to_get (str or int): The desired type of table
        """
        #Check whether the input is correct
        if self.debug:
            if not isinstance(attribute_to_get, (str, int)):
                raise TypeError(
                    f"attribute_to_get must be of type str or int, got {type(attribute_to_get)}."
                )

            if isinstance(attribute_to_get, str):
                if attribute_to_get not in self.attribute_schema:
                    raise KeyError(
                        f"'{attribute_to_get}' not found in attribute_idx. Available keys: {list(self.attribute_schema.keys())}"
                    )
        
        if isinstance(attribute_to_get, str):
            attribute_to_get = self.attribute_schema[attribute_to_get["idx"]]
        
        return self.env[:,:,attribute_to_get]
    
    def set_attributes(self, attributes_to_set: str | int, attribute_matrix: torch.Tensor) -> None:
        """
        Sets a given attribute matrix for the environment

        Args:
            attributes_to_set (str or int): The desired attribute matrix for the environment
            attribute_matrix (torch.Tensor): The updated attribute matrix
        """
        if self.debug:
            if attribute_matrix.shape != (self.n_agents, self.n_ressources):
                raise ValueError("Inventory must have shape (n_agents, n_ressources)")
            if not isinstance(attributes_to_set, (str, int)):
                raise TypeError(
                    f"attributes_to_set must be of type str or int, got {type(attributes_to_set)}."
                )

            if isinstance(attributes_to_set, str):
                if attributes_to_set not in self.attribute_schema:
                    raise KeyError(
                        f"'{attributes_to_set}' not found in attribute_idx. Available keys: {list(self.attribute_schema.keys())}"
                    )
        
        if isinstance(attributes_to_set, str):
            attributes_to_set = self.attribute_schema[attributes_to_set]

        self.env[:,:,attributes_to_set] = attribute_matrix
   