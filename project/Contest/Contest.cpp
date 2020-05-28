#include <vector>
#include <iostream>
#include <set>

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
//========================================================================================

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

//========================================================================================

int shortestPathLenght(const IGraph& graph, int from, int to) {
  std::vector<int> distance(graph.VerticesCount(), INT_MAX);
  distance[from] = 0;

  std::set<std::pair<int, int>> queue;
  queue.emplace(distance[from], from);

  while (!queue.empty()) {
    const auto& beginIt = queue.begin();
    auto currentVertex = beginIt->second;
    queue.erase(beginIt);

    const auto nextVertices = graph.GetNextVertices(currentVertex);
    for (const auto& [nextVertex, weight] : nextVertices) {
      if (distance[nextVertex] > distance[currentVertex] + weight) {
        if (distance[nextVertex] != INT_MAX) {
          queue.erase({distance[nextVertex], nextVertex});
        }
        distance[nextVertex] = distance[currentVertex] + weight;
        queue.emplace(distance[nextVertex], nextVertex);
      }
    }
  }
  return distance[to];
}

int main() {
  int vertexCount = 0;
  std::cin >> vertexCount;

  ListGraph<GraphType::Undirected> listGraph(vertexCount);

  int edgesCount = 0;
  std::cin >> edgesCount;

  for (int i = 0; i < edgesCount; ++i) {
    int from = 0;
    int to = 0;
    int weight = 0;
    std::cin >> from >> to >> weight;
    listGraph.AddEdge(from, to, weight);
  }

  int from = 0;
  int to = 0;
  std::cin >> from >> to;
  std::cout << shortestPathLenght(listGraph, from, to) << std::endl;

  return 0;
}
