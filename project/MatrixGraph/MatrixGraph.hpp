#pragma once

#include "IGraph.hpp"

class MatrixGraph : public IGraph {
public:
  MatrixGraph() = default;
  MatrixGraph(int vertexCount);
  MatrixGraph(const IGraph& rhs);

  void AddEdge(int from, int to) override;

  int VerticesCount() const override;

  std::vector<int> GetNextVertices(int vertex) const override;
  std::vector<int> GetPrevVertices(int vertex) const override;

private:
  std::vector<std::vector<int>> _adjacencyMatrix;
};