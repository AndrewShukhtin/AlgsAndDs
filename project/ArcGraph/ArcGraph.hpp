#pragma once

#include "IGraph.hpp"

#include <vector>
#include <unordered_set>

class ArcGraph : public IGraph {
public:
  ArcGraph() = default;
  ArcGraph(int vertexCount);
  ArcGraph(const IGraph& rhs);

  void AddEdge(int from, int to) override;

  int VerticesCount() const override;

  std::vector<int> GetNextVertices(int vertex) const override;
  std::vector<int> GetPrevVertices(int vertex) const override;

private:
  std::vector<std::pair<int, int>> _adjacencyContainer;
  std::unordered_set<int> _verticesCount;
};
