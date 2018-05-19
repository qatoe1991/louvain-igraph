import louvain
import igraph as ig 
from igraph import *

g = Graph.Formula('0 - 1 - 2 - 0, 2 - 3, 3 - 4 - 5 - 3')


#0-1, 1-2, 1-3, 0-4, 4-5, 4-6, 0-7, 0-8, 0-9')
#g= ig.Graph.Famous('Zachary')



opt = louvain.Optimiser()
partition = louvain.MapVertexPartition((g))#initial_membership=[0, 0, 0, 1, 1, 1])


diff = opt.move_nodes(partition)
print( partition)
print(diff)
