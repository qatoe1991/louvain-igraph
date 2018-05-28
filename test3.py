import io
import louvain
from igraph import *
import igraph as ig
import time
start_time = time.time()
running_time = time.time()-start_time


G = Graph.Read_Edgelist(
                        '/Users/kristiqato/Desktop/amazon.txt',
                        directed=False
                        )
g= G.clusters().giant()
opt = louvain.Optimiser()
partitions = louvain.find_partition(g,louvain.RBConfigurationVertexPartition, resolution_parameter =1.0)
improv = opt.optimise_partition(partitions)
test_file_to_save_output = '/Users/kristiqato/Desktop/kristi_results/amazon_RBConfiguration_louvain.txt'
for index in range (0, len(partitions)):
	partition_graph = g.subgraph(partitions[index])
	adhesion = partition_graph.cohesion(source = -1, target = -1, checks = True)
	density = partition_graph.density()
	cohesion = partition_graph.cohesion(source = -1, target = -1, checks = True, neighbors = "error")
	with io.FileIO(test_file_to_save_output, 'a') as f:
		f.write ("\n Partitison : {} \n ".format(index).encode('utf8'))
		f.write("Adhesion: {} \n".format(adhesion).encode('utf8'))
		f.write("Density: {} \n".format(density).encode('utf8'))
		f.write("Cohesion: {} \n".format(cohesion).encode('utf8'))


