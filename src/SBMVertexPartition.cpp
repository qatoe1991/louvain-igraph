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
<<<<<<< HEAD
    return new SBMVertexPartition(graph);
}

SBMVertexPartition*  SBMVertexPartition::create(Graph* graph, vector<size_t> const& membership)
{
    return new  SBMVertexPartition(graph, membership);
=======
  return new SBMVertexPartition(graph);
}

 SBMVertexPartition*  SBMVertexPartition::create(Graph* graph, vector<size_t> const& membership)
{
  return new  SBMVertexPartition(graph, membership);
>>>>>>> 6b11a72... Add new SBMVertexPartition
}

SBMVertexPartition::~SBMVertexPartition()
{ }
<<<<<<< HEAD


// calculatoin of  a and b
double SBMVertexPartition:: plogp(double p)
{
    return p > 0.0 ? p*log(p) : 0.0;
}

//double SBMVertexPartition:: clogc (double c)
//{
//    return c > 0.0 ? c * log2(c) : 0.0;
//}
double SBMVertexPartition:: getWeightBetweenCommunities(size_t r, size_t s)
{
    double weight_in_between = 0.0;
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
    
    
    
    if (new_comm != old_comm)
    {
        for (size_t t = 0; t < this->nb_communities(); t++)
        {
            
            if (t != old_comm && t != new_comm)
            {
                double m_rs = this->getWeightBetweenCommunities(old_comm,new_comm);
                std::cout<<"M_rs: "<<m_rs<<endl;
                double m_rt = this-> getWeightBetweenCommunities(old_comm, t);
                double m_st = this-> getWeightBetweenCommunities(new_comm, t);
                std::cout <<"M_rt: "<< m_rt<<endl;
                std::cout <<"M_st: "<<m_st<<endl;
                double k_it = this->getWeightBetweenCommunities(v,t);
                std::cout <<"K_it: " << k_it<<endl;
                double k_ir = this->weight_to_comm(v, old_comm);
                std::cout<<"K_ir : "<< k_ir<< endl;
                double k_is = this->weight_to_comm(v, new_comm);
                std::cout<<"K_is : "<< k_is<< endl;
                double m_rr = this->total_weight_in_comm(old_comm);
                double m_ss = this->total_weight_in_comm(new_comm);
                std::cout <<"M_rr: "<< m_rr<<endl;
                std::cout <<"M_ss: "<<m_ss<<endl;
                
                
                double k_i = this->graph->strength(v, IGRAPH_ALL);
                //double u_i = this->graph->node_self_weight(v);
                std::cout <<"K_i: "<< k_i<<endl;
                
                
                double kappa_r = this->total_weight_from_comm(old_comm);
                std::cout<<"Kappa r : "<< kappa_r<< endl;
                double kappa_s = this->total_weight_from_comm(new_comm);
                std::cout<<"Kappa s: "<< kappa_s << endl;
                
                
              
                //old community after
                double m_rt1 = m_rt-2*k_it;
                double m_st1 = m_st+2*k_it;
                std::cout <<"M_rt1 : "<< m_rt1 <<endl;
                std::cout <<"M_st1 : "<< m_st1 <<endl;
               
                
                //calculate the difference
               
                double between_comm_t  = 2*plogp(m_rt1)- 2*plogp(m_rt) + 2*plogp(m_st1)-2*plogp(m_st);
                
               
                
                double m_rs1 = m_rs +k_ir-k_is;
                
                double M_rs = 2*plogp(m_rs1)-2*plogp(m_rs);
                std::cout <<"M_rs1 : "<< m_rs1 <<endl;
               
                
                
                double m_rr1 = m_rr-k_ir;
                double m_ss1 = m_ss+k_is;
               
                double in_comm_weights = plogp(m_rr1) - plogp(m_rr) +plogp(m_ss1)- plogp(m_ss);
                std::cout <<"m_rr1 : "<< m_rr1 <<endl;
                std::cout <<"m_ss1 : "<< m_ss1 <<endl;
               
                
                double kappa_r1 = kappa_r-k_i;
                double kappa_s1 = kappa_s+k_i;
                
                double diff_kappa = -2*plogp(kappa_r1)+2*plogp(kappa_r) -2*plogp(kappa_s1) +2*plogp(kappa_s);
                std::cout <<"kapp_r1 : "<< kappa_r1 <<endl;
                std::cout <<"kapp_s1 : "<< kappa_s1 <<endl;
                
            
                std::cout <<"between_comm_t : "<< between_comm_t <<endl;
                std::cout <<"M_rs : "<< M_rs <<endl;
                std::cout <<"in_comm_weights:  "<< in_comm_weights<<endl;
                std::cout <<"diff_kappa : "<< diff_kappa <<endl;
                diff += between_comm_t +M_rs + in_comm_weights + diff_kappa;
                
                
                std::cout<<"DIFF : "<< diff<< endl;
            
                
               
            }
           
            
        }
       
       return diff;
        
    }
    //return diff;
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
            double weight_between = this->getWeightBetweenCommunities(r, s);
            double total_weight_r = this->total_weight_from_comm(r);
            double total_weight_s = this->total_weight_to_comm(s);
            cerr << "In between " << r << " and " << s << endl;
            cerr << "weight_between = " << weight_between << endl;
            cerr << "k_r = " << total_weight_r << endl;
            cerr << "k_s = " << total_weight_s << endl;
            if (weight_between > 0)
                sbm += weight_between*log(weight_between/(total_weight_r*total_weight_s));
        }
    }
    
    return sbm;
}

=======
            
//plogp
double SBMVertexPartition::plogp(double p)
{
    return p > 0.0 ? p * log2(p) : 3;
}

double SBMVertexPartition::diff_move(size_t v, size_t new_comm)
{
    return true;    
}


double SBMVertexPartition::quality()
{
    return true;
}
>>>>>>> 6b11a72... Add new SBMVertexPartition
