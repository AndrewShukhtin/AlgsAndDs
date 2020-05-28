#pragma once

#include "IGraph.hpp"

template <GraphType Type = GraphType::Directed>
class ListGraph : public IGraph {
public:
  ListGraph() = default;
  explicit ListGraph(int vertexCount);

  void AddEdge(int from, int to, int weight) override ;

  [[nodiscard]] int VerticesCount() const override;

  [[nodiscard]] std::vector<std::pair<int, int>> GetNextVertices(int vertex) const override;
  [[nodiscard]] std::vector<std::pair<int, int>> GetPrevVertices(int vertex) const override;

private:
  std::vector<std::vector<std::pair<int, int>>> _adjacencyLists;
};

template <GraphType Type>
ListGraph<Type>::ListGraph(int vertexCount) : _adjacencyLists(vertexCount) {}

template <GraphType Type>
int ListGraph<Type>::VerticesCount() const {
  return _adjacencyLists.size();
}

template <GraphType Type>
void ListGraph<Type>::AddEdge(int from, int to, int weight) {
  if constexpr (Type == GraphType::Directed) {
    _adjacencyLists[from].emplace_back(to, weight);
  } else {
    _adjacencyLists[from].emplace_back(to, weight);
    _adjacencyLists[to].emplace_back(from, weight);
  }
}

template <GraphType Type>
std::vector<std::pair<int, int>> ListGraph<Type>::GetNextVertices(int vertex) const {
  return _adjacencyLists[vertex];
}

template <GraphType Type>
std::vector<std::pair<int, int>> ListGraph<Type>::GetPrevVertices(int vertex) const {
  std::vector<std::pair<int, int>> res;
  for (int i = 0; i < VerticesCount(); ++i) {
    const auto nextVertices = GetNextVertices(i);
    for (const auto& [nextVertex, weight] : nextVertices) {
      if (nextVertex == vertex) {
        res.emplace_back(i, weight);
      }
    }
  }
  return res;
}