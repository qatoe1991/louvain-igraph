import io
from sklearn.metrics.cluster import normalized_mutual_info_score
from sklearn import metrics
#from __future__ import division
import numpy as np

from scipy import sparse

S = g = open("/Users/kristiqato/Desktop/amazon.txt", "r")
g = open("/Users/kristiqato/Desktop/kristi_results/amazon_leiden_map.txt", "r")
g1 = open("/Users/kristiqato/Desktop/kristi_results/amazon_louvain_map.txt", "r")

P1 =[g]
P2 = [g1]
#set_partition1 = [set(p) for p in P1]
#set_partition2 = [set(p) for p in P2]


def prob_dist(clustering, cluster, N):
    return len(clustering[cluster])/N

def prob_joint_dist(clustering1, clustering2, cluster1, cluster2, N):
    '''
    N(int): total number of elements.
    clustering1(list): first partition
    clustering2(list): second partition
    cluster1(int): index of cluster of the first partition
    cluster2(int): index of cluster of second partition
    '''
    c1 = clustering1[cluster1]
    c2 = clustering2[cluster2]
    n_ij = len(set(c1).intersection(c2))
    return n_ij/N

def mutual_info(clustering1, clustering2, N):
    '''
    clustering1(list): first partition
    clustering2(list): second partition
    Note for it to work division from  __future__ must be imported
    '''
    n_clas = len(clustering1)
    n_com = len(clustering2)
    mutual_info = 0
    for i in range(n_clas):
        for j in range(n_com):
            p_i = prob_dist(clustering1, i, N)
            p_j = prob_dist(clustering2, j, N)
            R_ij = prob_joint_dist(clustering1, clustering2, i, j, N)
            if R_ij > 0:
                mutual_info += R_ij*np.log( R_ij / (p_i * p_j))
    return mutual_info

comparison= mutual_info(P1,P2 , len(S))
print ("Comparison is: ", comparison)
		
		