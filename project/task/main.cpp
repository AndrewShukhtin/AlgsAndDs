#include <iostream>

#include "treap.hpp"
#include "binary_tree.hpp"

int main(void) {
  size_t nodes_count = 0;
  std::cin >> nodes_count;

  treap<int> trp;
  binary_tree<int> bt;
  for (size_t i = 0; i < nodes_count; ++i) {
    int value = 0;
    size_t priority = 0;
    std::cin >> value >> priority;

    bt.insert(value);
    trp.insert(value, priority);
  }

  std::cout << static_cast<int>(bt.height() - trp.height()) << std::endl;

  std::cout << trp.min_height() << std::endl;
  return EXIT_SUCCESS;
}
