#ifndef SBMVERTEXPARTITION_H
#define SBMVERTEXPARTITION_H

#include "MutableVertexPartition.h"
#include <iostream>
  using std::cerr;
  using std::endl;

class SBMVertexPartition: public MutableVertexPartition
{
  public:
    SBMVertexPartition(Graph* graph, vector<size_t> const& membership);
    SBMVertexPartition(Graph* graph, SBMVertexPartition* partition);
    SBMVertexPartition(Graph* graph);
    virtual ~SBMVertexPartition();
    virtual SBMVertexPartition* create(Graph* graph);
    virtual SBMVertexPartition* create(Graph* graph, vector<size_t> const& membership);

    virtual double diff_move(size_t v, size_t new_comm);
    virtual double quality();
    virtual double plogp(double p);
    virtual double getWeightBetweenCommunities(size_t r, size_t s);
  protected:
  private:
};

#endif // SBMVERTEXPARTITION_H
