#pragma once

#include <vector>

enum class GraphType {
  Directed,
  Undirected
};

class IGraph{
public:
  virtual ~IGraph()= default;

  virtual void AddEdge(int from, int to, int weight) = 0;

  [[nodiscard]] virtual int VerticesCount() const = 0;

  [[nodiscard]] virtual std::vector<std::pair<int, int>> GetNextVertices(int vertex) const = 0;
  [[nodiscard]] virtual std::vector<std::pair<int, int>> GetPrevVertices(int vertex) const = 0;
};