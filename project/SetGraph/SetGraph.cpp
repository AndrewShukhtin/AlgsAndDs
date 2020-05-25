#include "SetGraph.hpp"

SetGraph::SetGraph(int vertexCount) : _adjacencyContainer(vertexCount) {}

SetGraph::SetGraph(const IGraph& rhs) : _adjacencyContainer(rhs.VerticesCount()) {
  for (int i = 0; i < VerticesCount(); ++i) {
    const auto nextVertices = rhs.GetNextVertices(i);
    for (const auto& vertex: nextVertices)
      AddEdge(i, vertex);
  }
}

void SetGraph::AddEdge(int from, int to) {
  _adjacencyContainer[from].emplace(to);
}

int SetGraph::VerticesCount() const {
  return _adjacencyContainer.size();
}

std::vector<int> SetGraph::GetNextVertices(int vertex) const {
  return {_adjacencyContainer[vertex].begin(), _adjacencyContainer[vertex].end()};
}

std::vector<int> SetGraph::GetPrevVertices(int vertex) const {
  std::vector<int> res;
  for (int i = 0; i < VerticesCount(); ++i) {
    const auto& nextVertices = _adjacencyContainer[i];
    for (const auto& currentVertex: nextVertices) {
      if (currentVertex == vertex) {
        res.push_back(i);
      }
    }
  }
  return res;
}
