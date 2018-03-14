//
//  SBMVertexPartition.cpp
//  kristo
//
//  Created by Kristi Qato on 21/06/18.
//

#include "SBMVertexPartition.h"

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
