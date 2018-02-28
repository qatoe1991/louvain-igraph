//
//  MapEquationVertexPartition.cpp
//  kristo
//
//  Created by Kristi Qato on 21/06/18.
//

#include "MapVertexPartition.h"

MapVertexPartition::MapVertexPartition(Graph* graph,
      vector<size_t> const& membership) :
        MutableVertexPartition(graph,
        membership)
{ }

MapVertexPartition::MapVertexPartition(Graph* graph) :
        MutableVertexPartition(graph)
{ }

MapVertexPartition* MapVertexPartition::create(Graph* graph)
{
  return new MapVertexPartition(graph);
}

 MapVertexPartition*  MapVertexPartition::create(Graph* graph, vector<size_t> const& membership)
{
  return new  MapVertexPartition(graph, membership);
}

MapVertexPartition::~MapVertexPartition()
{ }
            
//plogp
double MapVertexPartition::plogp(double p)
{
    return p > 0.0 ? p * log2(p) : 0.0;
}

double MapVertexPartition::diff_move(size_t v, size_t new_comm)
{
    double diff =0.0;
    size_t old_comm = this->membership(v);
    // the total link weight of the node/module in the whole network
    // find the move that minimized the description length
#ifdef DEBUG
    cerr << "\t" << "graph_weight=" << graph_weight <<  "node_weight"  << node_weight << "." << endl;
#endif
    if (new_comm != old_comm)
    {
        // before move
        // the total weight of modules in the networks
        //double module_module_weights = this->total_weight_in_all_comms();
        
        // double node_weight = this->graph->strength(v, IGRAPH_ALL);
        double node_weight = 2.5;
        double graph_weight = this->graph->total_weight();
        //old module
        double old_length = 0.0;
        // relative module weight which is the total weights from the old module where v is part of
        double module_weight = this->total_weight_in_comm(old_comm);
        // exit module weight
        double exit_module_weight = this->weight_from_comm(v,old_comm);
        // all the links between modules condisedering the old module
        double old = 0.0;
        if (exit_module_weight >node_weight)
            { old = exit_module_weight-node_weight; }
        else {old = node_weight-exit_module_weight;}
        // calculate of the codelenght of the old module
        old_length = old* plogp(old) - 2*exit_module_weight* plogp(exit_module_weight) - (node_weight) * plogp(node_weight) + (exit_module_weight + module_weight)* plogp(exit_module_weight + module_weight);
    #ifdef DEBUG
        cerr << "\t" << "module_weight=" << module_weight << "exit_module_weight" << exit_module_weight << "old" << old << "." << endl;
    #endif
#ifdef DEBUG
        cerr << "\t" << "old_length" << old_length << "." << endl;
#endif
        // new module
        double new_length = 0.0;
        //exit module weight
        double new_module_weight = 2*this->weight_from_comm(v, new_comm);
        // total module weight
        double module_new= this->total_weight_in_comm(new_comm);
        
        double newM = 0.0;
        if(new_module_weight > node_weight){ newM = new_module_weight- node_weight ;}
        else {newM = node_weight-new_module_weight;}
        //calculate the codelength of the new module
        new_length = newM * plogp(newM)- 2*new_module_weight* plogp (new_module_weight)- (node_weight) * plogp(node_weight) + (new_module_weight + module_new)*log(new_module_weight + module_new);
    #ifdef DEBUG
        cerr << "\t" << "new_module_weight" << new_module_weight << "module_new" << module_new << "newM" << newM << "." << endl;
    #endif
    #ifdef DEBUG
        cerr << "\t" << "new_length" << new_length << "." << endl;
    #endif
        //calculate the diff
        diff = old_length - new_length;
        return diff;
    }
}

double MapVertexPartition::quality()
{
    return 12.0;
// MapEquationVertexPartition quality 
    #ifdef DEBUG
        cerr << "double MapEquationVertexPartition::quality()" << endl;
    #endif
        double mod= 0.0;
        double total_weight;
        
        if (this->graph->is_directed())
            return 0.0;
        else
            total_weight = 2*this->graph->total_weight();
    #ifdef DEBUG
        cerr << "\t" << "total_weight=" << total_weight << "." << endl;
    #endif
        for (size_t c = 0; c < this->nb_communities(); c++)
        {
            
            // size_t n_c = this->csize(c);
            // the total relative links of the community in the network;
            double comm_weight = this->graph->strength(c, IGRAPH_ALL);
            // the internal weight of the community
            double module_weight = this->total_weight_in_comm(c);
            // the exit links
            double exit_weights = comm_weight-module_weight;
            //all the links between modules
            double all = total_weight-module_weight;
    #ifdef DEBUG
            cerr << "\t" << ", comm_weight=" << comm_weight << ", module_weight=" << module_weight << ", exit_weights" << exit_weights << "all" << all << "." << endl;
    #endif
            //cacluate the codelengths
            
            mod = all*plogp(all) - 2*exit_weights *plogp(exit_weights) - comm_weight*plogp(comm_weight)+(exit_weights + module_weight)*plogp(exit_weights+module_weight);
        }
    #ifdef DEBUG
        cerr << "exit MapEquationVertexPartition::quality()" << endl;
        cerr << "return " << mod << endl << endl;
    #endif
        return mod;
}
