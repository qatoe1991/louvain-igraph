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

double MapVertexPartition::diff_move(size_t v, size_t new_comm)
{ return true; }

double MapVertexPartition::quality()
{ return false; }
