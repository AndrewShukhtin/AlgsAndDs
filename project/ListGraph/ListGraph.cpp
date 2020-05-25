#include "ListGraph.hpp"

#include <cassert>

ListGraph::ListGraph(int vertexCount) : _adjacencyLists(vertexCount) {}

ListGraph::ListGraph(const IGraph& rhs) : _adjacencyLists(rhs.VerticesCount()) {
  for (int i = 0; i < rhs.VerticesCount(); ++i) {
    _adjacencyLists[i] = rhs.GetNextVertices(i);
  }
}

int ListGraph::VerticesCount() const {
  return _adjacencyLists.size();
}

void ListGraph::AddEdge(int from, int to) {
  _adjacencyLists[from].push_back(to);
}

std::vector<int> ListGraph::GetNextVertices(int vertex) const {
  return _adjacencyLists[vertex];
}

std::vector<int> ListGraph::GetPrevVertices(int vertex) const {
  std::vector<int> res;
  for (int i = 0; i < VerticesCount(); ++i) {
    for (int j = 0; j < _adjacencyLists[i].size(); ++j) {
      if (_adjacencyLists[i][j] == vertex) {
        res.push_back(i);
      }
    }
  }
  return res;
}
