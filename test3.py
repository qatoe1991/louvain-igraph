import louvain
from igraph import *
import igraph as ig

g = Graph.Formula('0 - 1 - 2 - 0, 2 - 3, 3 - 4 - 5 - 3')
opt = louvain.Optimiser()
partition = louvain.SBMVertexPartition(g) #initial_membership=[0, 0, 0, 1, 1, 1])
q1 = partition.quality()
print(q1)
