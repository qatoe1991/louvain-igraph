import io

import louvain
from igraph import *
import time


g = Graph.Read_Edgelist(
	'/Users/kristiqato/Desktop/amazon.txt',
	directed=False
)

optimiser = louvain.Optimiser()
optimiser1 = leiden.Optimiser()

partitions = louvain.find_partition(g, louvain.MapVertexPartition)
partitions1 = leiden.find_partition(g, louvain.MapVertexPartition)
diff = optimiser.move_nodes(partitions)
diff1 = optimiser1.move_nodes(partitions1)
clusters = partitions.as_clustering()
clusters1 = partitions1.as_clustering()

membership = clusters.membership
membership1 = clusters1.memebership

comparison = graph.compare_communities(membership,memebership1, method = 'nmi', remove_node=False)

print ("Comparison is: ", comparison)
		
		