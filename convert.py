import networkx as nx
import numpy as np
import pandas as pd
import io

g= open( "/Users/kristiqato/Desktop/Map/zachary_karate.txt", 'rb')
G= nx.read_edgelist(g)
df = nx.to_pandas_adjacency(G, dtype = int)
df.values[np.diag_indices_from(df)] *= 2

print (df)