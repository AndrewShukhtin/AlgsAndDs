#pragma once

#include <iostream>
#include <stack>


template<class T>
struct binary_tree_node {
  binary_tree_node(T _value) : value(_value) {}
  T value = {};
  binary_tree_node* left = nullptr;
  binary_tree_node* right = nullptr;
};

template<class T, class Compare = std::less<T>>
class binary_tree {
  using element_type = T;
  using node_type = binary_tree_node<element_type>;
  using node_ptr_type = node_type*;

public:
  binary_tree() {}
  ~binary_tree();
  
  size_t height() const;

  void insert(element_type value);

  template<class Pred>
  void traverse_pre_order(Pred pred);

private:
  node_ptr_type _root = nullptr;
  Compare _cmp;
};

template<class T, class Compare>
binary_tree<T, Compare>::~binary_tree() {
  traverse_pre_order([](auto node){
    delete node;
  });
}

template<class T, class Compare>
void binary_tree<T, Compare>::insert(element_type value) {
  if (_root == nullptr) {
    _root = new node_type(value);
    return;
  }

  auto node = _root;
  while (true) {
    if (_cmp(node->value, value)) {
      if (node->right == nullptr) {
        node->right = new node_type(value);
        break;
      } else {
        node = node->right;
      }
    } else {
      if (node->left == nullptr) {
        node->left = new node_type(value);
        break;
      } else {
        node = node->left;
      }
    }
  }

  return;
}

template<class T, class Compare>
template<class Pred>
void binary_tree<T, Compare>::traverse_pre_order(Pred pred) {
  if (_root == nullptr) {
    return;
  }

  std::stack<node_ptr_type> stack;
  stack.push(_root);
  while (!stack.empty()) {
    auto node = stack.top();
    stack.pop();
    if (node->right != nullptr)
      stack.push(node->right);

    if (node->left != nullptr)
      stack.push(node->left);

    pred(node);
  }
}

template<class T, class Compare>
size_t binary_tree<T, Compare>::height() const {
  if (_root == nullptr) {
    return 0;
  }

  std::queue<node_ptr_type> queue;
  queue.push(_root);

  size_t height = 0;
  while (true) {
    size_t node_count = queue.size();
    if (node_count == 0) {
      return height;
    }

    ++height;
    while (node_count > 0) {
      node_ptr_type node = queue.front();

      queue.pop();

      if (node->left != nullptr)
        queue.push(node->left);

      if (node->right != nullptr)
        queue.push(node->right);

      --node_count;
    }
  }
}
