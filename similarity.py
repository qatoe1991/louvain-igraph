import io
import louvain
from igraph import *
import igraph as ig
import time
start_time = time.time()
running_time = time.time()-start_time

def get_partitions():
	partitions12 = []
	with open("/Users/kristiqato/Desktop/amazon_comm.txt", "r") as f:
		for line in f:
			partition = line.split()
			partitions12.append(list(int(i) for i in partition))
	return partitions12

G = Graph.Read_Edgelist(
                        '/Users/kristiqato/Desktop/amazon.txt',
                        directed=False
                        )
g= G.clusters().giant()
opt = louvain.Optimiser()
partitions = louvain.MapVertexPartition(g)
diff = opt.move_nodes(partitions)
partitions1 = get_partitions()
				

sum_of_vertices = 0
couples_of_vertices = []

for part in partitions:
	part_graph = g.subgraph(part)

for part in partitions1:
	part_graph = G.subgraph(part)

for v in g.vs:
	u = g.neighbors(v, mode = ALL)
	for i in u:
		b = False
		c = False
		a = set([v.index, i])
		if a not in couples_of_vertices:
			couples_of_vertices.append(a)
			for part in partitions:
				part_graph = g.subgraph(part)
				try:
					if part_graph.are_connected(part.index(v.index), part.index(i)):
						b = True
						break
				except (ig._igraph.InternalError, ValueError):
					pass
					
			for part in partitions1:
				part_graph = G.subgraph(part)
				try:
					if part_graph.are_connected(part.index(v.index), part.index(i)):
						c = True
						break
				except (ig._igraph.InternalError, ValueError):
					pass
			if b and c:
				sum_of_vertices += 1
print("SUMMMM: ", sum_of_vertices)


	

