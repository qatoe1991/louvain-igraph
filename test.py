import louvain
from igraph import *
import igraph as ig

#g = Graph.Read_Edgelist('/Users/kristiqato/Desktop/facebook.txt', directed=False)
#print(g.is_directed())
#sys.exit(0)
#g = Graph.Read_GML('/Users/kristiqato/Desktop/dolphins.gml')
#g = Graph.Formula('0 - 1 - 2 - 0, 2 - 3, 3 - 4 - 5 - 3')
g= ig.Graph.Famous('Zachary')
opt = louvain.Optimiser()
#partition = louvain.MapVertexPartition(g, initial_membership=[0, 0, 0, 1, 1, 1])
partition = louvain.SBMVertexPartition(g)

for v in g.vs:
    comms = list(set([partition.membership[u] for u in g.neighbors(v)]))
    q1 = partition.quality()
    diff = partition.diff_move(v.index, comms[0])
    partition.move_node(v.index, comms[0])
    q2 = partition.quality()
    if (round(diff, 6) != round(q2 - q1, 6)):
        print('Moving node {0} to {1} inconsistent improvement'.format(v.index, comms[0]))
        print('diff = {0}, q2 - q1 = {1}'.format(diff, q2 - q1))

#opt.optimise_partition(partition)
#while opt.move_nodes(partition) > 0:
#    print(partition.graph.vcount())
#    partition = partition.aggregate_partition()
#diff = opt.move_nodes(partition)
#print(partition)
