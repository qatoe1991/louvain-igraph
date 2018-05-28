import louvain
import igraph as ig 
from igraph import *

g = Graph.Formula('0 - 1 - 2 - 0, 2 - 3, 3 - 4 - 5 - 3')


#0-1, 1-2, 1-3, 0-4, 4-5, 4-6, 0-7, 0-8, 0-9')
#g= ig.Graph.Famous('Zachary')
#g=Graph.Read_Edgelist( '/Users/kristiqato/Desktop/email.txt',directed=False)
#g= G.clusters().giant()


opt = louvain.Optimiser()
partition = louvain.SBMVertexPartition(g)#initial_membership=[0, 0, 0, 1, 1, 1])


#diff = opt.move_nodes(partition)
#diff1 = partition.diff_move(3,1)
diff = partition.diff_move(3,0)
print(diff)
print(partition)
#q = partition.quality()
#partition.move_node(3,0)
#print(partition.quality() - q)

