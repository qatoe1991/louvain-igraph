#ifndef MAPVERTEXPARTITION_H
#define MAPVERTEXPARTITION_H

#include "MutableVertexPartition.h"
#include <iostream>
  using std::cerr;
  using std::endl;

class MapVertexPartition: public MutableVertexPartition
{
  public:
    MapVertexPartition(Graph* graph, vector<size_t> const& membership);
    MapVertexPartition(Graph* graph, MapVertexPartition* partition);
    MapVertexPartition(Graph* graph);
    virtual ~MapVertexPartition();
    virtual MapVertexPartition* create(Graph* graph);
    virtual MapVertexPartition* create(Graph* graph, vector<size_t> const& membership);

    virtual double diff_move(size_t v, size_t new_comm);
    virtual double quality();
    virtual double plogp(double p);
  protected:
  private:
};

#endif // MAPVERTEXPARTITION_H
