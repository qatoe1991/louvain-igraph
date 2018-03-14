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
    return p > 0.0 ? p * log2(p) : 1;
}

double MapVertexPartition::diff_move(size_t v, size_t new_comm)
{
#ifdef DEBUG
    cerr << "double MapEquationVertexPartition::diff_move(" << v << ", " << new_comm << ")" << endl;
#endif
    double diff = 0.0;
    size_t old_comm = this->membership(v);
    double t_w = 2*this->graph->total_weight();
    double w = this->total_weight_in_all_comms();
    
    if (new_comm != old_comm){
        
        //L(M) = w_exit*log(w_exit)-2sum(m,i=1)w_m_exit*log(w_m_exit)+sum(m,i=1)(w_m_exit+w_m)*log(w_m_exit+w_m)
        
        double v_s = this->graph->strength(v, IGRAPH_ALL);
        //old comm
        double in_old = this->total_weight_in_comm(old_comm); // internal weight of the old_comm
        double w_v_old = this->weight_from_comm(v,old_comm);// the total weight between v and old_com
        double w_old = this->total_weight_from_comm(old_comm);// the total weight of links in old_comm
        //new comm
        double in_new = this->total_weight_in_comm(new_comm);// internal weight of the new_comm
        double w_v_new = this->weight_from_comm(v,new_comm);// the total weight between v and new_Comm
        double w_new = this->total_weight_from_comm(new_comm);//the total weight of links in new_com
        
        //Before move v to the other community L(M)
        
        // the total weight of the link exiting old module
        double exit_old = w_old - in_old; // the links that goes outside the old module
        // do i need to calculate the exiting links before move as the links that exit old_comm + the link that exit v (not including the link inside old_comm)??
        double exit_v = v_s- w_v_old;   // the total weight of the links that link v with other nodes but not the nodes inside the old_comm
        //double exiting = e + e_v; // so the overall link going outsie the old module + the links that goes outside v.
        
        // the total weight of the links exiting new module
        double exit_new = w_new- in_new;
        
        // the total weight between modules
        double w_b_m = (t_w - w)/t_w;
        
        //After the move v to the new community
       
        //old module
        
        double w_old1 = w_old - v_s; // the weight of old module
        double exit_old1 = exit_old + w_v_old - exit_v; // the total exiting weights of old_comm
        
        //new module
        
        double w_new1 = w_new + v_s; //of the new module
        // the total exiting weight of new comm
        double exit_v_new = v_s - w_v_new; // all the links that go outside v to new_comm but not with the nodes inside new_comm
        double exit_new1 = exit_new -w_v_new +  exit_v_new;
      
        // the total weight between modules
        double w2 = w_b_m + w_v_old - w_v_new;
        double w_b_m1 = (t_w-w2)/t_w;
        
        // codelength term  (delta between terms)
        
        // the exit weights
        double old_module_exit = 2* exit_old1 * plogp(exit_old1) - 2* exit_old* plogp(exit_old);
        double new_module_exit = 2*exit_new1*plogp(exit_new1) - 2*exit_new*plogp(exit_new);
        double module_exit = new_module_exit - old_module_exit;
        
        // the exit weight between modules
        double exit_between_modules = w_b_m1*plogp(w_b_m1)- w_b_m*plogp(w_b_m);
        
        // the module weight
        double old_module_weight = (exit_old1 + w_old1) *plogp(exit_old1 + w_old1) - (exit_old + w_old)*plogp(exit_old + w_old);
        double new_module_weight = (exit_new1 +w_new1)*plogp(exit_new1+w_new1) - (exit_new+w_new)*plogp(exit_new+w_new);
        double module_weight = new_module_weight - old_module_weight;
        
        // Calculation of L(M)
        double diff = exit_between_modules*plogp(exit_between_modules) - 2*module_exit*plogp(module_exit) +(module_exit+module_weight)*plogp(module_exit+module_weight);
    
    }
    return diff;
    
    }


double MapVertexPartition::quality()
{
#ifdef DEBUG
    cerr << "double MapEquationVertexPartition::quality()" << endl;
#endif
    double mod= 0.0;
    double total_weight = 2*this->graph->total_weight();
    double w = this->total_weight_in_all_comms();
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
        //double exit_weights= (comm_weight-module_weight)/total_weight;
        double exit_weights= (1-module_weight)/total_weight;
        //all the links between modules
        double all = (total_weight -w)/total_weight;
#ifdef DEBUG
        cerr << "\t" << "n_c=" << n_c << ", comm_weight=" << comm_weight << ", module_weight=" << module_weight << ", exit_weights" << exit_weights << "all" << all << "." << endl;
#endif
        //cacluate the codelengths
        
        mod = all*plogp(all) - 2*exit_weights * plogp(exit_weights) + (exit_weights + comm_weight)* plogp(exit_weights + comm_weight);
    }
#ifdef DEBUG
    cerr << "exit MapEquationVertexPartition::quality()" << endl;
    cerr << "return " << mod << endl << endl;
#endif
    return mod;
}
