#include <vector>
#include <iostream>
#include <queue>

enum class GraphType {
  Directed,
  Undirected
};

class IGraph{
public:
  virtual ~IGraph()= default;

  virtual void AddEdge(int from, int to) = 0;

  virtual int VerticesCount() const = 0;

  virtual std::vector<int> GetNextVertices(int vertex) const = 0;
  virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};

//========================================================================================

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

//========================================================================================

int ShortPathCount(const IGraph& graph, int from, int to) {
  std::vector<int> distance(graph.VerticesCount(), INT_MAX);
  distance[from] = 0;

  std::vector<int> pathCount(graph.VerticesCount(), 0);
  pathCount[from] = 1;

  std::queue<int> queue;
  queue.push(from);

  while (!queue.empty()) {
    auto currentVertex = queue.front();
    queue.pop();
    auto nextVertices = graph.GetNextVertices(currentVertex);
    for (const auto& nextVertex : nextVertices) {
      if (distance[nextVertex] == INT_MAX) {
        distance[nextVertex] = distance[currentVertex] + 1;
        pathCount[nextVertex] = pathCount[currentVertex];
        queue.push(nextVertex);
      } else if (distance[nextVertex] == distance[currentVertex] + 1) {
        pathCount[nextVertex] += pathCount[currentVertex];
      }
    }
  }
  return pathCount[to];
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
    std::cin >> from >> to;
    listGraph.AddEdge(from, to);
  }

  int from = 0;
  int to = 0;
  std::cin >> from >> to;
  std::cout << ShortPathCount(listGraph, from, to) << std::endl;

  return 0;
}
