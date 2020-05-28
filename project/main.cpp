#include "ListGraph.hpp"

#include <iostream>
#include <vector>
#include <set>

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
      if (distance[nextVertex] > distance[currentVertex] + 1) {
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
