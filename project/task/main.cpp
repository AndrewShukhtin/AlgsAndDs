#include <iostream>

#include "binary_tree.hpp"

int main(void) {
  size_t number_count = 0;
  std::cin >> number_count;

  binary_tree<int> bt;
  for (size_t i = 0; i < number_count; ++i) {
    int number = 0;
    std::cin >> number;
    bt.insert(number);
  }

  bt.traverse_pre_order([](auto node){
    std::cout << node->value << std::endl;
  });

  return EXIT_SUCCESS;
}
