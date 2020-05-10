#include <iostream>
#include "avl_tree.hpp"

int main(void) {

  avl_tree<int> tree;
  avl_tree<int>::kstat_finder kstat_finder(tree);

  size_t commads_count = 0;
  std::cin >> commads_count;
  for (size_t i = 0; i < commads_count; ++i) {
    int key = 0;
    size_t kstat_place = 0;
    std::cin >> key >> kstat_place;
    
    if (key > 0) {
      tree.insert(key);
    } else {
      tree.erase(std::abs(key));
    }

    std::cout << kstat_finder(kstat_place) << std::endl;
  }

  return EXIT_SUCCESS;
}