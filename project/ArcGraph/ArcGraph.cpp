#include "ArcGraph.hpp"

#include <unordered_set>

ArcGraph::ArcGraph(int vertexCount) : _adjacencyContainer(vertexCount) {}

ArcGraph::ArcGraph(const IGraph& rhs) {
  for (int i = 0; i < rhs.VerticesCount(); ++i) {
    auto nextVertices = rhs.GetNextVertices(i);
    for (const auto& vertex: nextVertices)
      AddEdge(i, vertex);
  }
}

void ArcGraph::AddEdge(int from, int to) {
  _verticesCount.emplace(from);
  _adjacencyContainer.emplace_back(from, to);
}

int ArcGraph::VerticesCount() const {
  return _verticesCount.size();
}

std::vector<int> ArcGraph::GetNextVertices(int vertex) const {
  std::vector<int> res;
  for (const auto& [from, to]: _adjacencyContainer) {
    if (from == vertex) {
      res.push_back(to);
    }
  }
  return res;
}

std::vector<int> ArcGraph::GetPrevVertices(int vertex) const {
  std::vector<int> res;
  for (const auto& [from, to]: _adjacencyContainer) {
    if (to == vertex) {
      res.push_back(from);
    }
  }
  return res;
}