#pragma once

#include "IGraph.hpp"

class ListGraph : public IGraph {
public:
  ListGraph() = default;
  explicit ListGraph(int vertexCount);

  explicit ListGraph(const IGraph& rhs);

  void AddEdge(int from, int to) override;

  int VerticesCount() const override;

  std::vector<int> GetNextVertices(int vertex) const override;
  std::vector<int> GetPrevVertices(int vertex) const override;

private:
  std::vector<std::vector<int>> _adjacencyLists;
};
