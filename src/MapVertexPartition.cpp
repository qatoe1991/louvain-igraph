//  MapEquationVertexPartition.cpp
//  kristo
//
//  Created by Kristi Qato on 21/06/18.
//

#include "MapVertexPartition.h"
#include <math.h>
#include <iostream>


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
    return p > 0.0 ? p*log(p) : 0;
}

double MapVertexPartition::diff_move(size_t v, size_t new_comm)
{
    //std::cout << "double MapEquationVertexPartition::diff_move(" << v << ", " << new_comm << ")" << endl;

    double diff = 0.0;
    size_t old_comm = this->membership(v);
    double t_w = 2*this->graph->total_weight();
    double w = 2*this->total_weight_in_all_comms();
    //std::cout << "Total weight " << t_w << endl;
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
        
       // std::cout << "Comm\tInternal weight\tWeight between\tTotal weight" << std::endl;
        //std::cout << old_comm << "\t" << in_old << "\t" << w_v_old << "\t" << w_old << std::endl;
        //std::cout << new_comm << "\t" << in_new << "\t" << w_v_new << "\t" << w_new << std::endl;
        //Before move v to the other community L(M)
        
        // the total weight of the link exiting old module
        double exit_old = w_old - 2*in_old; // the links that goes outside the old module
        //std::cout << "Before move: Old module exit weight is " << exit_old << std::endl;
        // the total weight of the links exiting new module
        double exit_new = w_new - 2*in_new;
        //std::cout << "Before move: new module exit weight is " << exit_new << std::endl;
        
        // the total weight between modules
        double w_m = t_w-w; // the weights between modules
        double w_b_m = w_m /t_w; //normalized
        //std::cout << "Before move: Total weight between is " << w_m << std::endl;
        //std::cout << "Before move: Total normalised weight between is " << w_b_m << std::endl;
        
        //After the move v to the new community
        
        //old module
        double w_old1 = w_old - v_s; // the weight of old module
        //std::cout << "After move: Old module weight is " << w_old1 << std::endl;
        double exit_v = v_s - w_v_old;   // the total weight of the links that link v with other nodes but not the nodes inside the old_comm
        //std::cout << "After move: Exit v old " << exit_v << std::endl;
        double exit_old1 = exit_old - exit_v + w_v_old; // the total exiting weights of old_comm
        //std::cout << "After move: Old module exit weight is " << exit_old1  << std::endl;
        
        //new module
        double w_new1 = w_new + v_s; //the total weight of the new module
        //std::cout << "After move: New module weight is " << w_new1 << std::endl;
        double exit_v_new = v_s - w_v_new; // all the links that go outside v to new_comm but not with the nodes in the new_comm
        //std::cout << "After move: Exit v new " << exit_v_new << std::endl;
        double exit_new1 = exit_new + exit_v_new - w_v_new;// the total exiting weight of new comm
        //std::cout << "After move: new module exit weight is " << exit_new1  << std::endl;
        
        // the total weight between modules
        double w_m1 = w_m + 2*w_v_old - 2*w_v_new;
        double w_b_m1 = w_m1/t_w;
        //std::cout << "After move: Total weight between is " << w_m1 << std::endl;
        //std::cout << "After move: Total normalised weight between is " << w_b_m1 << std::endl;
        
        // codelength term  (delta between terms)
        
        // the exit weight
        double old_module_exit = -2*plogp(exit_old1/t_w) + 2*plogp(exit_old/t_w);
        //std::cout << "Old module exit weight is " << old_module_exit << endl;
        
        double new_module_exit = -2*plogp(exit_new1/t_w) + 2*plogp(exit_new/t_w);
        //std::cout << "New module exit weight is " << new_module_exit << endl;
        
        double module_exit_diff = new_module_exit + old_module_exit;
        //std::cout << "The exit weights are " << module_exit_diff << endl;
        
        // the exit weight between modules
        double exit_between_modules_diff = plogp(w_b_m1) - plogp(w_b_m);
        //std::cout << "The weight between modules is: " << exit_between_modules_diff << endl;
        
        // the module weight
        double old_module_weight = plogp((exit_old1 + w_old1)/t_w) - plogp((exit_old + w_old)/t_w);
        //std::cout << "Old module weight difference is " << old_module_weight << endl;
        double new_module_weight = plogp((exit_new1 + w_new1)/t_w) - plogp((exit_new + w_new)/t_w);
        //std::cout << "New module weight difference is " << new_module_weight << endl;
        double module_weight_diff = new_module_weight + old_module_weight;
        //std::cout << "Module weight diffference is " << module_weight_diff << endl;
        
        // Calculation of L(M)
        
        diff = exit_between_modules_diff + module_exit_diff + module_weight_diff;
        //std::cout << "The diffference is " << diff << endl;
    }
    return -diff;
}


double MapVertexPartition::quality()
{
#ifdef DEBUG
    cerr << "double MapEquationVertexPartition::quality()" << endl;
#endif
    double mod= 0.0;
    double total_weight = 2*this->graph->total_weight();
    double w = 2*this->total_weight_in_all_comms();
#ifdef DEBUG
    cerr << "\t" << "total_weight=" << total_weight << "." << endl;
#endif
    double all = 1 - w/total_weight;
    mod = plogp(all);
    
    for (size_t c = 0; c < this->nb_communities(); c++)
    {
        
        
        // the total relative links of the community in the network;
        double comm_weight = this->total_weight_from_comm(c);
        // the internal weight of the community
        double module_weight = this->total_weight_in_comm(c);
        // the exit links
        double exit_weight= comm_weight-2*module_weight;
        
        //all the links between modules
        //double all = (total_weight -w)/total_weight;
#ifdef DEBUG
        cerr << "\t" << ", comm_weight=" << comm_weight << ", module_weight=" << module_weight << ", exit_weights" << exit_weights << "all" << all << "." << endl;
#endif
        //cacluate the codelengths
        
        mod += -2*plogp(exit_weight/total_weight) + plogp((exit_weight + comm_weight)/total_weight);
    }
    
    for (size_t v = 0; v < this->graph->vcount(); v++)
    {
        double v_s = this->graph->strength(v, IGRAPH_ALL);
        v_s /= total_weight;
        mod += plogp(v_s);
    }
    
    
#ifdef DEBUG
    cerr << "exit MapEquationVertexPartition::quality()" << endl;
    cerr << "return " << mod << endl << endl;
#endif
    return -mod;
}


