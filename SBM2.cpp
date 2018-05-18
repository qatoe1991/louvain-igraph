
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
    
    std::cout << "\n \n double SBMEquationVertexPartition::diff_move(" << v << ", " << new_comm << ")" << endl;
    
    double diff = 0.0;
    size_t old_comm = this->membership(v);
    
    
    if (new_comm != old_comm)
    {
        double m_rr = this->total_weight_in_comm(old_comm);
        std::cout <<"M_RR : "<<m_rr<<endl;
        double m_ss = this->total_weight_in_comm(new_comm);
        std::cout <<"M_SS: "<<m_ss<<endl;
        double k_ir = this->weight_from_comm(v, old_comm);
        double k_is = this->weight_from_comm(v, new_comm);
        std::cout<<"K_ir: "<< k_ir<< endl;
        std::cout<<"K_is: "<< k_is<< endl;
        double kappa_r = this->total_weight_from_comm(old_comm);
        double kappa_s = this->total_weight_from_comm(new_comm);
        std::cout<<"Kappa_r: "<< kappa_r<< endl;
        std::cout<<"Kappa_s: "<< kappa_s<< endl;
        double k_i = this->graph->strength(v, IGRAPH_ALL);
        double u_i = this->graph->node_self_weight(v);
        
        std::cout<<"K_i: "<< k_i<< endl;
        
        for (size_t t = 0; t < this->nb_communities(); t++)
        {
            
           
            if (t != old_comm && t != new_comm)
            {
                double m_rs = 0.0;
                
               
                
                set<size_t> comm_nodes = this->get_community(old_comm);
                for (std::set<size_t>::iterator it = comm_nodes.begin();
                     it != comm_nodes.end(); ++it)
                {
                    size_t u = *it; // u is a node in r
                    m_rs += this->weight_to_comm(u, new_comm);
                }
                if (old_comm == new_comm)
                    m_rs /= 2.0;
                std::cout<<"M_rs: "<<m_rs<<endl;
                
                
                
                double m_rt = this->weight_from_comm(old_comm, t);
                double m_st = this->weight_from_comm(new_comm, t);
                std::cout <<"M_rt: "<<m_rt<<endl;
                std::cout <<"M_st: "<<m_st<<endl;
                //double m_rr = this->total_weight_in_comm(old_comm);
                //double m_ss = this->total_weight_in_comm(new_comm);
                //std::cout <<"Links in old_comm: "<<m_rr<<endl;
                
                double k_it = this->weight_from_comm(v,t);
                std::cout <<"K_it: "<<k_it<<endl;
               
                //double k_ir = this->weight_from_comm(v, old_comm);
                //double k_is = this->weight_from_comm(v, new_comm);
                //std::cout<<"Links between v and old_comm: "<< k_ir<< endl;
                
                //double kappa_r = this->total_weight_from_comm(old_comm);
                //double kappa_s = this->total_weight_from_comm(new_comm);
                
                //double k_i = this->graph->strength(v, IGRAPH_ALL);
                
                double exit_links= 2*plogp(m_rt-k_it)- 2*plogp(m_rt)+2*plogp(m_st+k_it)-2*plogp(m_st);
                
                double between_r_s = 2*plogp(m_rs+k_ir-k_is) - 2*plogp(m_rs);
                
                double in_degree = plogp(m_rr-2*k_ir)-plogp(m_rr)+plogp(m_ss+2*k_is)- plogp(m_ss);
                
                double total_links = -2*plogp(kappa_r-2*(k_i+u_i))+2*plogp(kappa_r)-2*plogp(kappa_s+2*(k_i+u_i))+2*plogp(kappa_s);
                
                diff += exit_links +between_r_s +in_degree +total_links;
                std::cout<<"the difference is: "<<diff<<endl;
            }
        }
        
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
            double weight_in_between = 0.0;
            set<size_t> comm_nodes = this->get_community(r);
            for (std::set<size_t>::iterator it = comm_nodes.begin();
                 it != comm_nodes.end(); ++it)
            {
                size_t u = *it; // u is a node in r
                weight_in_between += this->weight_to_comm(u, s);
            }
            if (r == s)
                weight_in_between /= 2.0;
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

