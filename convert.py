import networkx as nx
import numpy as np
import pandas as pd
import io

g= open("/Users/kristiqato/Desktop/amazon.txt", 'rb')
G= nx.read_edgelist(g)
df = nx.to_pandas_adjacency(G, dtype = int)
df.values[np.diag_indices_from(df)] *= 2

test_file_to_save_output = '/Users/kristiqato/Desktop/kristi_results/convert.txt'
with io.FileIO(test_file_to_save_output, 'a') as f:
	f.write (format(df).encode('utf8'))

