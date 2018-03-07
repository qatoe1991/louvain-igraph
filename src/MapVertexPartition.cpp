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
#ifdef DEBUG
    cerr << "double MapEquationVertexPartition::diff_move(" << v << ", " << new_comm << ")" << endl;
#endif
    double diff = 0.0;
    size_t old_comm = this->membership(v);
    double t_w = this->graph->total_weight();
    double w = this->total_weight_in_all_comms();
    
    if (new_comm!=old_comm){
    
    //L(M) = w_exit*log(w_exit)-2sum(m,i=1)w_m_exit*log(w_m_exit)+sum(m,i=1)(w_m_exit+w_m)*log(w_m_exit+w_m)
        
        double v = this->graph->strength(v, IGRAPH_ALL);
        
    //old comm
        double w_old = this-> total_weight_in_comm(old_comm);
        double w_v_old = this->weight_from_comm(v,old_comm);
        double out_old = this->total_weight_from_comm(old_comm);
    //new comm
        double w_new = this->total_weight_in_comm(new_comm);
        double w_v_new = this->weight_from_comm(v,new_comm);
        double new_out = this->total_weight_from_comm(old_comm);
        
    //Before move v to the other community L(M)
    // the total weight of the link exiting old module
        double e = out_old - w_old; // the links that goes outside the old module
        double e_v = v- w_v_old;   // the total weight of the links that link v with other nodes but not the nodes inside the old_comm
        double exiting = e + e_v;
    // the total weight of the links exiting new module
        double e_new = new_out- w_new;
    // the total weight between modules
        double m = 1 - w/2*t_w;
        
    //After the move v to the new community
    //module weight
        double old = out_old - v;
        double new_c = new_out + v;
        
    // the total exiting weights of old_comm
        double o_old = e + w_v_old - e_v;
    // the total exiting weight of new comm
        double e_v_n = v - w_v_new; // all the links that go outside v to new_comm but not with the nodes inside new_comm
        double o_new = e_new -w_v_new +  e_v_n;
    // the total weight between modules
        double w1 = m + w_v_old - w_v_new;
        
    // codelength term before move (delta between terms)
        double old_module_exit = 2*o_old*plogp(o_old) - 2*e*plogp(e);
        double new_module_exit = 2*o_new*plogp(o_new) - 2* e_new*plogp(e_new);
        double module_exit = new_module_exit - old_module_exit;
        
        double exit_between_modules = w1*plogp(w1)- m*plogp(m);
        
        double old_module_weight = (o_old+old)*plogp(o_old+old)-(exiting + out_old)*plogp(exiting + out_old);
        double new_module_weight = (o_new+new_c)*plogp(o_new+new_c) - (e_new+new_out)*plogp(e_new+new_out);
        double module_weight = new_module_weight - old_module_weight;
        
    // Calculation of L(M)
        double diff = exit_between_modules*plogp(exit_between_modules) - 2*module_exit*plogp(module_exit)+(module_exit+module_weight)*plogp(module_exit+module_weight);
    
    }
    return diff;
    
    }


double MapVertexPartition::quality()
{
#ifdef DEBUG
    cerr << "double MapEquationVertexPartition::quality()" << endl;
#endif
    double mod= 0.0;
    double total_weight;
    double exit_weights = 0.0;
    double all = 0.0;
    
    if (this->graph->is_directed())
    return 0.0;
    else
    total_weight = 2*this->graph->total_weight();
#ifdef DEBUG
    cerr << "\t" << "total_weight=" << total_weight << "." << endl;
#endif
    for (size_t c = 0; c < this->nb_communities(); c++)
    {
        
        size_t n_c = this->csize(c);
        // the total relative links of the community in the network;
        double comm_weight = this->total_weight_from_comm(c);
        // the internal weight of the community
        double module_weight = this->total_weight_in_comm(c);
        // the exit links
        double exit_weights= comm_weight-module_weight;
        //all the links between modules
        double all = 1 - this->total_weight_in_all_comms()/total_weight;
#ifdef DEBUG
        cerr << "\t" << "n_c=" << n_c << ", comm_weight=" << comm_weight << ", module_weight=" << module_weight << ", exit_weights" << exit_weights << "all" << all << "." << endl;
#endif
        //cacluate the codelengths
        
        mod = all*plogp(all) - 2*exit_weights *plogp(exit_weights) + (exit_weights + comm_weight)* plogp(exit_weights+comm_weight);
    }
#ifdef DEBUG
    cerr << "exit MapEquationVertexPartition::quality()" << endl;
    cerr << "return " << mod << endl << endl;
#endif
    return mod;
}
