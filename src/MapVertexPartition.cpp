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
    return p > 0.0 ? p * log2(p) : 3;
}

double MapVertexPartition::diff_move(size_t v, size_t new_comm)
{
#ifdef DEBUG
    cerr << "double MapEquationVertexPartition::diff_move(" << v << ", " << new_comm << ")" << endl;
#endif
    double diff = 0.0;
    size_t old_comm = this->membership(v);
    double t_w = 2*this->graph->total_weight();
    double w = this->total_weight_in_all_comms(); // Is this supposed to be the internal weight between module and not the wieght between modules??
    
    if (new_comm!=old_comm){
        
        //L(M) = w_exit*log(w_exit)-2sum(m,i=1)w_m_exit*log(w_m_exit)+sum(m,i=1)(w_m_exit+w_m)*log(w_m_exit+w_m)
        
        double v = this->graph->strength(v, IGRAPH_ALL);
        //old comm
        double w_old = this->total_weight_in_comm(old_comm); // internal weight of the old_comm
        double w_v_old = this->weight_from_comm(v,old_comm);// the total weight between v and old_com
        double out_old = this->total_weight_from_comm(old_comm);// the total weight of links in old_comm
        //new comm
        double w_new = this->total_weight_in_comm(new_comm);// internal weight of the new_comm
        double w_v_new = this->weight_from_comm(v,new_comm);// the total weight between v and new_Comm
        double new_out = this->total_weight_from_comm(old_comm);//the total weight of links in new_com
        
        //Before move v to the other community L(M)
        
        // the total weight of the link exiting old module
        double e = out_old - w_old; // the links that goes outside the old module
        // do i need to calculate the exiting links before move as the links that exit old_comm + the link that exit v (not including the link inside old_comm)??
        double e_v = v- w_v_old;   // the total weight of the links that link v with other nodes but not the nodes inside the old_comm
        double exiting = e + e_v; // so the overall link going outsie the old module + the links that goes outside v.
        // the total weight of the links exiting new module
        double e_new = new_out- w_new;
        // the total weight between modules
        double m = 1 - w/t_w; // in doubt with this ?
        
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
        double w1 = m + w_v_old - w_v_new; // still in doubt for m??
        
        // codelength term  (delta between terms)
        double old_module_exit = 2*o_old*plogp(o_old) - 2*exiting*plogp(exiting);
        double new_module_exit = 2*o_new*plogp(o_new) - 2*e_new*plogp(e_new);
        double module_exit = new_module_exit - old_module_exit;
        
        double exit_between_modules = w1*plogp(w1)- m*plogp(m);
        
        double old_module_weight = (o_old+old)*plogp(o_old+old) -(e + out_old)*plogp(e + out_old);
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
   
    
    if (this->graph->is_directed())
    return 0.0;
    else
    total_weight = 2*this->graph->total_weight();
#ifdef DEBUG
    cerr << "\t" << "total_weight=" << total_weight << "." << endl;
#endif
    for (size_t c = 0; c < this->nb_communities(); c++)
    {
        
        
        // the total relative links of the community in the network;
        double comm_weight = this->total_weight_from_comm(c);
        // the internal weight of the community
        double module_weight = this->total_weight_in_comm(c);
        // the exit links
        double exit_weights= comm_weight-module_weight;
        //all the links between modules
        double all = total_weight - module_weight;
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
