import io
import louvain
from igraph import *
import igraph as ig
import time
start_time = time.time()
running_time = time.time()-start_time


g= ig.Graph.Famous('Zachary')
opt = louvain.Optimiser()
partitions = louvain.MapVertexPartition(g)
diff = opt.move_nodes(partitions)
partitions1=louvain.SurpriseVertexPartition(g)
diff1 = opt. move_nodes(paritions)
neigh = g.neighborhood(vertices = None, oder = 1,mode = ALL)
print(partition)
for v in g.vs:
	u = g.neighbors(v, mode = ALL)
	for i in u:
		a = set(v.index, i) 
			
	

