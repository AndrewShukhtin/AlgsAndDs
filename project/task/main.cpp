#include <iostream>

#include "hashtable.hpp"

class task_hasher {
public:
  size_t operator()(const std::string& str) const {
    static constexpr size_t kDefaultPolynomialHashValue = 7;
    size_t hash = 0;
    for (const auto& c : str)
      hash = hash * kDefaultPolynomialHashValue + c;
    
    return hash;
  }
};

int main(void) {

  hash_table<std::string, task_hasher> ht;

  char operation = 0;
  std::string key;

  auto pred = [](bool res) {
    if (res) {
      std::cout << "OK" << std::endl;
    } else {
      std::cout << "FAIL" << std::endl;
    }
  };

  while (std::cin >> operation >> key) {
    switch (operation) {
    case '+':
      pred(ht.insert(key));
      break;

    case '-':
      pred(ht.remove(key));
      break;

    case '?':
      pred(ht.has(key));
      break;

    default:
      break;
    }
  }

  return EXIT_SUCCESS;
}
