
//  SBMVertexPartition.cpp
//  kristo
//
//  Created by Kristi Qato on 21/06/18.
//

#include "SBMVertexPartition.h"

#include <iostream>
#include <math.h>



SBMVertexPartition::SBMVertexPartition(Graph* graph,
                                       vector<size_t> const& membership) :
MutableVertexPartition(graph,
                       membership)
{ }

SBMVertexPartition::SBMVertexPartition(Graph* graph) :
MutableVertexPartition(graph)
{ }

SBMVertexPartition* SBMVertexPartition::create(Graph* graph)
{
    return new SBMVertexPartition(graph);
}

SBMVertexPartition*  SBMVertexPartition::create(Graph* graph, vector<size_t> const& membership)
{
    return new  SBMVertexPartition(graph, membership);
}

SBMVertexPartition::~SBMVertexPartition()
{ }


// calculatoin of  a and b
double SBMVertexPartition:: plogp(double p)
{
    return p > 0.0 ? p*log(p) : 0.0;
}

//double SBMVertexPartition:: clogc (double c)
//{
//    return c > 0.0 ? c * log2(c) : 0.0;
//}


// diff function

double SBMVertexPartition::diff_move(size_t v, size_t new_comm)
{
    
    //cerr << "double MapEquationVertexPartition::diff_move(" << v << ", " << new_comm << ")" << endl;
    
    std::cout << "double SBMEquationVertexPartition::diff_move(" << v << ", " << new_comm << ")" << endl;
    
    double diff = 0.0;
    size_t old_comm = this->membership(v);
    double t_w = 2*this->graph->total_weight();
    std::cout <<"Total wieght of the graph: "<<t_w<<endl;
    //double w = this->total_weight_in_all_comms();
    
    if (new_comm != old_comm)
    {
        
        // the number of links between two communities (old community and new community)
        double edge_weight_between_old_and_new = 0.0;
        set<size_t> nodes_in_old_comm = this->get_community(old_comm);
        for (std::set<size_t>::iterator it = nodes_in_old_comm.begin();
             it != nodes_in_old_comm.end(); ++it)
        {
            size_t u = *it; // u is a node in old_comm
            edge_weight_between_old_and_new += this->weight_from_comm(u, new_comm);
            
        }
        std::cout << "Before move edge between old and new comm  "<< edge_weight_between_old_and_new << endl;
        
        // Before move
        double u = this->graph->node_self_weight(v); // the self edges of the node
        double v_total = this->graph->strength(v, IGRAPH_ALL);// the total degree of the node v
        std::cout << "Total degree of the node v  "<< v_total << endl;
        double v_degree = v_total - u;// the total degree not including self edges
        std::cout << "Degree of the node v-u  "<< v_degree << endl;
        
        
        //OLD COMMUNITY
        std::cout<<"Old Community "<<endl;
        // the total degree of the old community.
        double old_total = this->total_weight_from_comm(old_comm);
        std::cout << "The total degree of the old comm:  "<< old_total << endl;
        // the links between the v and the old_comm
        double v_w_old = this->weight_to_comm(v,old_comm);
        std::cout << "Links between v and the old_comm:  "<< v_w_old << endl;
        // intern weight of commu
        double in_old= this->total_weight_in_comm(old_comm);
        std::cout <<"In degree old comm: "<< in_old <<endl;
        double old_degree =old_total - 2*in_old;
        std::cout<<"The exit links of old community:  "<<old_degree<<endl;
        double v_out_old = v_degree - v_w_old;
        std:: cout <<"Exit links of v in old_comm: "<<v_out_old<<endl;
        
        //NEW COMMUNITY
        std::cout<<"New Community"<<endl;
        // the number of nodes of the new_com
        double new_total = this->total_weight_from_comm(new_comm);
        std::cout << "The total degree of the new comm:  "<< new_total << endl;
        // the links between the v and the new_comm
        double v_w_new =this->weight_from_comm(v,new_comm);
        std::cout << "Links between v and the new_comm:  "<< v_w_new << endl;
        double in_new= this->total_weight_in_comm(new_comm);
        std::cout << "In degree of new comm:  "<< in_new << endl;
        double new_degree = new_total - 2*in_new; // the degree not including the in degree
        std::cout<<"The exit links of new community:  "<< new_degree<<endl;
        double v_out_new = v_total - v_w_new;
        std::cout<<"Exit links of v in new_comm:  "<< v_out_new <<endl;
        
        // After the move
        std::cout<<"After Move"<< endl;
        // the links between the new_comm and the old_comm
        double edge_weight_between_old_and_new1 = edge_weight_between_old_and_new + v_w_old - v_w_new;
        std::cout << "The edges between two communities:  "<< edge_weight_between_old_and_new1 << endl;
        
        // the total degree of the communities after move
        std::cout<<"Old Community "<< endl;
        double old_degree1 = old_degree - v_out_old + 2*v_w_old;
        std::cout << "Exit links of old comm:  "<< old_degree1 << endl;
        double old_total1 = old_total- v_total;
        std::cout << "Total degree of old comm: "<< old_total1<< endl;
        std::cout<<"New Community "<<endl;
        double new_degree1 = new_degree + 2*v_out_new - v_w_new;
        std::cout << "Exit links the new comm:  "<< new_degree1 << endl;
        double new_total1= new_total + v_total;
        std::cout<<"Total degree of new comm: "<< new_total1<< endl;
        
        // calculate the difference
        std::cout<<"The difference calculation"<< endl;
        double total_edges = 2*plogp(old_degree1/t_w) - 2* plogp(old_degree/t_w ) + 2*plogp(new_degree1/t_w) - 2*plogp(new_degree/t_w);
        std::cout <<"Total Edges:  "<< total_edges<< endl ;
        
        double between_modules = 2*plogp(edge_weight_between_old_and_new1/t_w)- 2*plogp(edge_weight_between_old_and_new/t_w);
        std::cout <<"Between modules:  "<< between_modules << endl ;
        
        double self_old = plogp(in_old/t_w - 2*(v_w_old+u)/t_w) - plogp(in_old/t_w)+ plogp(in_new/t_w + 2*(v_w_new+u)/t_w) - plogp(in_new/t_w);
        std::cout <<"Self old:  "<< self_old << endl;
        
        double degrees = -2*plogp(old_total1/t_w)+ 2*plogp(old_total/t_w) - 2*plogp(new_total1/t_w) + 2*plogp(new_total/t_w);
        std::cout <<"Degrees:  "<< degrees << endl ;
        
        diff = total_edges + between_modules +self_old + degrees;
        std::cout << "Diff:  "<< diff << endl;
        
        
    }
    return diff;
}
// the quality
double SBMVertexPartition::quality()
{
    //#ifdef DEBUG
    //cerr << "double SBMEquationVertexPartition::quality()" << endl;
    //#endif
    double sbm =0.0;
    size_t n = 2*this->graph->total_weight();
    
    for (size_t c = 0; c < this->nb_communities(); c++)
    {
        //size_t csize = this->csize(c);
        double c_total = this->total_weight_from_comm(c); // the total number of edges of the c
        double c_in = this->total_weight_in_comm(c);// the total number of edges inside c
        double c_d = c_total-2*c_in; // the total number of edges not includin inside edges
        
        sbm += c_d/n *plogp((c_d/c_total*(n-c_total))/n);
        
    }
    return sbm;
}

