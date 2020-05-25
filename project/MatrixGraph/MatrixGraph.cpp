#include "MatrixGraph.hpp"

MatrixGraph::MatrixGraph(int vertexCount) : _adjacencyMatrix(vertexCount, std::vector<int>(vertexCount, 0)) {}

MatrixGraph::MatrixGraph(const IGraph& rhs)
: _adjacencyMatrix(rhs.VerticesCount(), std::vector<int>(rhs.VerticesCount(), 0)) {
  for (int i = 0; i < rhs.VerticesCount(); ++i) {
    auto nextVertices = rhs.GetNextVertices(i);
    for (const auto& vertex: nextVertices) {
      _adjacencyMatrix[i][vertex] = 1;
    }
  }
}

void MatrixGraph::AddEdge(int from, int to) {
  _adjacencyMatrix[from][to] = 1;
}

int MatrixGraph::VerticesCount() const {
  return _adjacencyMatrix.size();
}

std::vector<int> MatrixGraph::GetNextVertices(int vertex) const {
  std::vector<int> res;
  const auto& row = _adjacencyMatrix[vertex];
  for (int i = 0; i < VerticesCount(); ++i) {
    if (row[i]) {
      res.push_back(i);
    }
  }
  return res;
}

std::vector<int> MatrixGraph::GetPrevVertices(int vertex) const {
  std::vector<int> res;
  for (int i = 0; i < VerticesCount(); ++i) {
    if (_adjacencyMatrix[i][vertex]) {
      res.push_back(i);
    }
  }
  return res;
}
