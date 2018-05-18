
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

double getWeightBetweenCommunities(size_t r, size_t s)
{
    set<size_t> comm_nodes = this->get_community(r);
    for (std::set<size_t>::iterator it = comm_nodes.begin();
         it != comm_nodes.end(); ++it)
    {
        size_t u = *it; // u is a node in r
        weight_in_between += this->weight_to_comm(u, s);
    }
    if (s == r)
        weight_in_between /= 2.0;
    return weight_in_between;
}

// diff function
double SBMVertexPartition::diff_move(size_t v, size_t new_comm)
{
    
    //cerr << "double MapEquationVertexPartition::diff_move(" << v << ", " << new_comm << ")" << endl;
    
    std::cout << "\n \n double SBMEquationVertexPartition::diff_move(" << v << ", " << new_comm << ")" << endl;
    
    double diff = 0.0;
    size_t old_comm = this->membership(v);
    //double t_w = 2*this->graph->total_weight();
    //std::cout <<"\n Total wieght of the graph: "<<t_w<<endl;
    //double w = this->total_weight_in_all_comms();
    
    if (new_comm != old_comm)
    {
        for (size_t t = 0; t < this->nb_communities(); t++)
        {
            if (t != old_comm && t != new_comm)
            {
                double m_rt = this->getWeightBetweenCommunities(r, t);
                double m_st = this->getWeightBetweenCommunities(s, t);
                
                double m_rr = this->getWeightBetweenCommunities(r, r);
                double m_ss = this->getWeightBetweenCommunities(s,s);
                
                double k_it = this->weight_to_comm(v, t);
                double k_ir = this->weight_to_comm(v, r);
                
                double kappa_r = this->total_weight_from_comm(r);
                double kappa_s = this->total_weight_from_comm(s);
                
                k_i = this->grah->strength(v);
                
                diff += ...
            }
        }
        // the number of links between two communities (old community and new community)
        double edge_weight_between_old_and_new = 0.0;
        set<size_t> nodes_in_old_comm = this->get_community(old_comm);
        for (std::set<size_t>::iterator it = nodes_in_old_comm.begin();
             it != nodes_in_old_comm.end(); ++it)
        {
            size_t u = *it; // u is a node in old_comm
            edge_weight_between_old_and_new += this->weight_from_comm(u, new_comm);
            
        }
       // std::cout << "\n Before move edge between old and new comm  "<< edge_weight_between_old_and_new << endl;
        
        // Before move
        //double u = this->graph->node_self_weight(v); // the self edges of the node
        double v_total = this->graph->strength(v, IGRAPH_ALL);// the total degree of the node v
        std::cout << "\n Total degree of the node v  "<< v_total << endl;
        double v_degree = v_total - u;// the total degree not including self edges
        std::cout << "\n Degree of the node v-u  "<< v_degree << endl;
        
        
        //OLD COMMUNITY
        std::cout<<"\n \n Old Community "<<endl;
        // the total degree of the old community.
        double old_total = this->total_weight_from_comm(old_comm);
        std::cout << "\n The total degree of the old comm:  "<< old_total << endl;
        // the links between the v and the old_comm
        double v_w_old = this->weight_to_comm(v,old_comm);
        std::cout << "\n Links between v and the old_comm:  "<< v_w_old << endl;
        // intern weight of commu
        double in_old= this->total_weight_in_comm(old_comm);
        std::cout <<"\n In degree old comm: "<< in_old <<endl;
        double old_degree =old_total - 2*in_old;
        std::cout<<"\n The exit links of old community:  "<<old_degree<<endl;
        double v_out_old = v_degree - v_w_old;
        std:: cout <<"\n Exit links of v in old_comm: "<<v_out_old<<endl;
        
        //NEW COMMUNITY
        std::cout<<"\n \n New Community"<<endl;
        // the number of nodes of the new_com
        double new_total = this->total_weight_from_comm(new_comm);
        std::cout << "\n The total degree of the new comm:  "<< new_total << endl;
        // the links between the v and the new_comm
        double v_w_new =this->weight_from_comm(v,new_comm);
        std::cout << "\n Links between v and the new_comm:  "<< v_w_new << endl;
        double in_new= this->total_weight_in_comm(new_comm);
        std::cout << "\n In degree of new comm:  "<< in_new << endl;
        double new_degree = new_total - 2*in_new; // the degree not including the in degree
        std::cout<<"\n The exit links of new community:  "<< new_degree<<endl;
        double v_out_new = v_total - v_w_new;
        std::cout<<"\n Exit links of v in new_comm:  "<< v_out_new <<endl;
        
        // After the move
        std::cout<<"\n \n After Move"<< endl;
        // the links between the new_comm and the old_comm
        double edge_weight_between_old_and_new1 = edge_weight_between_old_and_new + v_w_old - v_w_new;
        std::cout << "The edges between two communities:  "<< edge_weight_between_old_and_new1 << endl;
        
        // the total degree of the communities after move
        std::cout<<"\n \n Old Community "<< endl;
        double old_degree1 = old_degree - v_out_old + v_w_old;
        std::cout << "Exit links of old comm:  "<< old_degree1 << endl;
        double old_total1 = old_total- v_total;
        std::cout << "Total degree of old comm: "<< old_total1<< endl;
        std::cout<<"\n \n New Community "<<endl;
        double new_degree1 = new_degree + v_out_new - v_w_new;
        std::cout << "Exit links the new comm:  "<< new_degree1 << endl;
        double new_total1= new_total + v_total;
        std::cout<<"Total degree of new comm: "<< new_total1<< endl;
        double old_in_degree1 = in_old - (v_w_old + u);
        std::cout << "The new in degree of old comm is: "<<old_in_degree1<<endl;
        double new_in_degree1 = in_new + (v_w_new+u);
        std::cout<<"The new in degree of new comm is:  "<< new_in_degree1<<endl;
        
        // calculate the difference
        std::cout<<"\n \nThe difference calculation"<< endl;
        double total_edges = 2*plogp(old_degree1) - 2* plogp(old_degree) + 2*plogp(new_degree1) - 2*plogp(new_degree);
        std::cout <<"\n Total Edges:  "<< total_edges<< endl ;
        
        double between_modules = 2*plogp(edge_weight_between_old_and_new1)- 2*plogp(edge_weight_between_old_and_new);
        std::cout <<"\n Between modules:  "<< between_modules << endl ;
        
        double in_degrees = plogp((old_in_degree1) - (in_old))+ plogp((new_in_degree1) - (in_new));
        //double self_old = plogp(in_old/t_w - 2*(v_w_old+u)/t_w) - plogp(in_old/t_w)+ plogp(in_new/t_w + 2*(v_w_new+u)/t_w) - plogp(in_new/t_w);
        std::cout <<"\n In degrees:  "<< in_degrees << endl;
        
        double degrees = -2*plogp(old_total1)+ 2*plogp(old_total) - 2*plogp(new_total1) + 2*plogp(new_total);
        std::cout <<"\n Degrees:  "<< degrees << endl ;
        
        diff = total_edges + between_modules + in_degrees + degrees;
        std::cout << "\n Diff:  "<< diff << endl;
        
        
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
    
    
    for (size_t r = 0; r < this->nb_communities(); r++)
    {
        for (size_t s = 0; s < this->nb_communities(); s++)
        {
            double weight_in_between = this->getWeightBetweenCommunities(r, s);
            double total_weight_r = this->total_weight_from_comm(r);
            double total_weight_s = this->total_weight_to_comm(s);
            cerr << "In between " << r << " and " << s << endl;
            cerr << "weight_between = " << weight_in_between << endl;
            cerr << "k_r = " << total_weight_r << endl;
            cerr << "k_s = " << total_weight_s << endl;
            if (weight_in_between > 0)
                sbm += weight_in_between*log(weight_in_between/(total_weight_r*total_weight_s));
        }
    }
    
    return sbm;
}

