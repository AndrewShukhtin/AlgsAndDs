#pragma once

#include "IGraph.hpp"

template <GraphType Type = GraphType::Directed>
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


template <GraphType Type>
ListGraph<Type>::ListGraph(int vertexCount) : _adjacencyLists(vertexCount) {}


template <GraphType Type>
ListGraph<Type>::ListGraph(const IGraph& rhs) : _adjacencyLists(rhs.VerticesCount()) {
  for (int i = 0; i < rhs.VerticesCount(); ++i) {
    _adjacencyLists[i] = rhs.GetNextVertices(i);
  }
}


template <GraphType Type>
int ListGraph<Type>::VerticesCount() const {
  return _adjacencyLists.size();
}


template <GraphType Type>
void ListGraph<Type>::AddEdge(int from, int to) {
  if constexpr (Type == GraphType::Directed) {
    _adjacencyLists[from].push_back(to);
  } else {
    _adjacencyLists[from].push_back(to);
    _adjacencyLists[to].push_back(from);
  }
}

template <GraphType Type>
std::vector<int> ListGraph<Type>::GetNextVertices(int vertex) const {
  return _adjacencyLists[vertex];
}

template <GraphType Type>
std::vector<int> ListGraph<Type>::GetPrevVertices(int vertex) const {
  std::vector<int> res;
  for (int i = 0; i < VerticesCount(); ++i) {
    const auto nextVertices = GetNextVertices(i);
    for (const auto& nextVertex : nextVertices) {
      if (nextVertex == vertex) {
        res.push_back(i);
      }
    }
  }
  return res;
}