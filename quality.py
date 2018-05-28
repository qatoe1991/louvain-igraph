import louvain
from igraph import *
import igraph as ig



def get_partitions():
	partitions = []
	with open("/Users/kristiqato/Desktop/amazon_comm.txt", "r") as f:
		for line in f:
			partition = line.split()
			partitions.append(list(int(i) for i in partition))
	return partitions
				

g = Graph.Read_Edgelist(
                        '/Users/kristiqato/Desktop/amazon.txt',
                        directed=False
                        )
                        
                        
                   
opt = louvain.Optimiser()
part1 = louvain.MapVertexPartition(g)
impor1 = opt.optimise_partition(part1)
part2 = get_partitions()
#for index in range(0, len(part)):
	#partition_graph = g.subgraph(part[index])
#print (part)

#g1 = part1.cluster_graph()
#membership = part1.clusters()
#g2 = part2.cluster_graph()
#membership1 = part2.clusters()
#print(part2)
#print (g2)
#print(g1)
comp = compare_communities(part1, part2, method="nmi")
print (comp)