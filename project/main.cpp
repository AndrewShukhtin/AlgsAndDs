#include "ListGraph.hpp"
#include "MatrixGraph.hpp"
#include "SetGraph.hpp"
#include "ArcGraph.hpp"

#include <iostream>
#include <vector>

bool testNextVertices(const IGraph& lhs, const IGraph& rhs) {
  auto verticesCount = lhs.VerticesCount();
  for (int i = 0; i < verticesCount; ++i) {
    auto lhsNextVertices = lhs.GetNextVertices(i);
    auto rhsNextVertices = rhs.GetNextVertices(i);
    if (lhsNextVertices != rhsNextVertices) {
      return false;
    }
  }
  return true;
}

bool testPrevVertices(const IGraph& lhs, const IGraph& rhs) {
  auto verticesCount = lhs.VerticesCount();
  for (int i = 0; i < verticesCount; ++i) {
    auto lhsPrevVertices = lhs.GetPrevVertices(i);
    auto rhsPrevVertices = rhs.GetPrevVertices(i);
    if (lhsPrevVertices != rhsPrevVertices) {
      return false;
    }
  }
  return true;
}

bool testInterfaceFunctions(const IGraph& lhs, const IGraph& rhs) {
  if (lhs.VerticesCount() != rhs.VerticesCount()) {
    return false;
  }

  if (!testNextVertices(lhs, rhs)) {
    return false;
  }

  return testPrevVertices(lhs, rhs);
}

bool testingFunction(const IGraph& testingGraph){
  {
    ListGraph listGraph(testingGraph);
    if (!testInterfaceFunctions(listGraph, testingGraph)) {
      return false;
    }
  }

  {
    MatrixGraph matrixGraph(testingGraph);
    if (!testInterfaceFunctions(matrixGraph, testingGraph)) {
      return false;
    }
  }

  {
    SetGraph setGraph(testingGraph);
    if (!testInterfaceFunctions(setGraph, testingGraph)) {
      return false;
    }
  }

  {
    ArcGraph arcGraph(testingGraph);
    if (!testNextVertices(testingGraph, arcGraph)) {
      return false;
    }

    if (!testPrevVertices(testingGraph, arcGraph)) {
      return false;
    }
  }
  return true;
}

int main() {
  ListGraph listGraph(5);
  listGraph.AddEdge(0, 2);
  listGraph.AddEdge(1, 0);
  listGraph.AddEdge(1, 2);
  listGraph.AddEdge(1, 4);
  listGraph.AddEdge(2, 3);
  listGraph.AddEdge(3, 4);
  listGraph.AddEdge(4, 2);
  listGraph.AddEdge(4, 3);


  if (!testingFunction(listGraph)) {
    std::cout << "TEST FAILED" << std::endl;
  } else {
    std::cout << "TEST PASSED" << std::endl;
  }

  return 0;
}

