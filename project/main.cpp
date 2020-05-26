#include "ListGraph.hpp"

#include <iostream>
#include <vector>
#include <queue>

template<class Visit>
void BFS(const IGraph& graph, int from, Visit visit) {
  std::vector<bool> visited(graph.VerticesCount(), false);

  std::queue<int> queue;
  queue.push(from);
  visited[from] = true;
  while (!queue.empty()) {
    auto vertex = queue.front();
    queue.pop();
    visit(vertex);
    auto nextVertices = graph.GetNextVertices(vertex);
    for (const auto& nextVertex : nextVertices) {
      if (!visited[nextVertex]) {
        queue.push(nextVertex);
        visited[nextVertex] = true;
      }
    }
  }
}

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

